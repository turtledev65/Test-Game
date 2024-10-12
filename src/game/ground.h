#pragma once

#include <cglm/cglm.h>
#include <cglm/mat4.h>

#include "game/camera.h"
#include "game/tile.h"
#include "gfx/instanced-mesh.h"

typedef struct {
  InstancedMesh mesh;
} Ground;

void Ground_init(Ground *self, Tiles *tiles);
void Ground_draw(Ground *self, Camera *camera);
