#pragma once

#include "cglm/types-struct.h"

typedef struct {
  vec3s pos;
  vec3s target;

  float theta, phi;

  float radius;
  float zoom;
} Camera;


void Camera_init(Camera *self, float radius);
void Camera_update(Camera *self);
void Camera_getViewMatrix(Camera *self, mat4 dest);
void Camera_getProjectionMatrix(Camera *self, vec2s *windowSize, mat4 dest);
