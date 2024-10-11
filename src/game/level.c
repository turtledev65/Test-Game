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

    switch (src[i]) {
    case PLAYER_CHAR:
      Player_init(&self->player, (vec3){col, 0.0f, row});
      break;
    case GROUND_CHAR:
      DYN_ARR_PUSH(&self->tiles, ((Tile){.col = col, .row = row}));
      break;
    default:
      break;
    }
  }
  free(src);

  // Init ground mesh
  float vertices[] = {
      -1.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.0f,
      1.0f,  1.0f, 0.0f, 1.0f,  -1.0f, 0.0f,
  };
  unsigned int indices[] = {
      0, 1, 2, 1, 2, 3,
  };
  mat4 modelMatrices[self->tiles.length];
  for (int i = 0; i < self->tiles.length; i++) {
    mat4 model = GLM_MAT4_IDENTITY_INIT;
    glm_translate(model,
                  (vec3){self->tiles.data[i].x, -2.0f, self->tiles.data[i].z});
    glm_rotate(model, glm_rad(90.0f), (vec3){1.0f, 0.0f, 0.0f});
    glm_mat4_copy(model, modelMatrices[i]);
  }
  InstancedMesh_init(&self->ground, self->tiles.length, modelMatrices, vertices,
                     sizeof(vertices) / sizeof(vertices[0]), indices,
                     sizeof(indices) / sizeof(indices[0]));

  // Init the camera
  Camera_init(&self->camera);
  glm_vec3_copy(self->player.sprite.pos.raw, self->camera.target.raw);
}

void Level_draw(Level *self)
{

  InstancedMesh_draw(&self->ground, &self->camera);
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
