#pragma once

#include <cglm/types-struct.h>
#include "game/camera.h"
#include "gfx/texture.h"

typedef struct {
  vec3s pos;
  vec3s rotation;
  vec3s scale;

  Texture texture;
} Sprite;

void Sprite_init(Sprite *self, GLenum format, const char *path);
void Sprite_draw(Sprite *self, Camera *camera);
