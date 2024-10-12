#pragma once

#include "game/tile.h"
#include "gfx/instanced-mesh.h"

typedef struct {
  InstancedMesh mesh;
} Wall;

void Wall_init(Wall *self, Tiles *tiles);
void Wall_draw(Wall *self, Camera *camera);
