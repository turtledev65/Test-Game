#include "level.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game/player.h"

#include "util/dynamic-array.h"
#include "util/file.h"

#include <cglm/cglm.h>

#define GROUND_CHAR '.'
#define PLAYER_CHAR 'P'
#define WALL_CHAR '#'

#define TILE_SCALE 2.0f

// Public Functions
void Level_init(Level *self, const char *path)
{
  DYN_ARR_INIT(&self->tiles);

  char *src = readFile(path);
  if (src == NULL) {
    return;
  }

  // Get dimensions
  size_t length = strlen(src);
  size_t width  = 0;
  while (src[width] != '\n') {
    width++;
  }
  size_t height = length / width;

  // Transform the string into a matrix
  size_t row = 0;
  size_t col = 0;
  for (int i = 0; i < length; i++, col++) {
    if (src[i] == '\n') {
      row++;
      col = 0;
      continue;
    }

    char ch = src[i];
    switch (ch) {
    case PLAYER_CHAR:
      Player_init(&self->player,
                  (vec3){col * TILE_SCALE, 0.0f, row * TILE_SCALE});
      DYN_ARR_PUSH(&self->tiles, ((Tile){.col  = col * TILE_SCALE,
                                         .row  = row * TILE_SCALE,
                                         .type = TILE_GROUND}));
      break;
    case GROUND_CHAR:
      DYN_ARR_PUSH(&self->tiles, ((Tile){.col  = col * TILE_SCALE,
                                         .row  = row * TILE_SCALE,
                                         .type = TILE_GROUND}));
      break;
    case WALL_CHAR: {
      bool isWall = ((i > 0 && src[i - 1] == GROUND_CHAR) ||
                     (i < length - 1 && src[i + 1] == GROUND_CHAR)) ||
                    ((row > 0 && src[i - (width + 1)] == GROUND_CHAR) ||
                     (row < height - 1 && src[i + width + 1] == GROUND_CHAR)) ||
                    ((row > 0 && src[i - width] == GROUND_CHAR) ||
                     (row < height - 1 && src[i + width] == GROUND_CHAR)) ||
                    ((row > 0 && src[i - width - 2] == GROUND_CHAR) ||
                     (row < height - 1 && src[i + width + 2] == GROUND_CHAR));

      if (isWall) {
        DYN_ARR_PUSH(&self->tiles, ((Tile){.col  = col * TILE_SCALE,
                                           .row  = row * TILE_SCALE,
                                           .type = TILE_WALL}));
      }
    } break;
    default:
      break;
    }
  }
  free(src);

  // Init the camera
  Camera_init(&self->camera);
  Ground_init(&self->ground, &self->tiles);
  Wall_init(&self->wall, &self->tiles);
  glm_vec3_copy(self->player.sprite.pos.raw, self->camera.target.raw);
}

void Level_draw(Level *self)
{
  Ground_draw(&self->ground, &self->camera);
  Wall_draw(&self->wall, &self->camera);
  Player_draw(&self->player, &self->camera);
}

void Level_update(Level *self, float deltaTime)
{
  Camera_update(&self->camera);
  Player_update(&self->player, deltaTime);

  // Update the target to the player's position
  vec3s target = {
      .x = self->player.sprite.pos.x,
      .y = 0.0f, // don't follow the player's y position
      .z = self->player.sprite.pos.z,
  };
  glm_vec3_lerp(self->camera.target.raw, target.raw, 0.05f,
                self->camera.target.raw);
}
