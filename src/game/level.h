#pragma once

#include "game/player.h"

#include "gfx/instanced-mesh.h"
#include "util/dynamic-array.h"

typedef struct {
  union {
    size_t col;
    size_t x;
  };
  union {
    size_t row;
    size_t z;
  };
} Tile;

typedef struct {
  Camera camera;
  Player player;

  DYN_ARR(Tile) tiles;
  InstancedMesh ground;
} Level;

void Level_init(Level *self, const char *path);
void Level_update(Level *self, float deltaTime);
void Level_draw(Level *self);
