#pragma once

#include <cglm/types-struct.h>
#include "game/camera.h"

typedef struct {
  vec3s pos;
  vec3s scale;
  vec3s color;
} Plane;

void Plane_init(Plane *self, vec3s pos, vec3s scale);
void Plane_draw(Plane *self, Camera *camera);
