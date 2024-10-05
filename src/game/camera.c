#include "camera.h"

#include "cglm/cam.h"

static vec3 worldUp = {0.0f, 1.0f, 0.0f};

void Camera_init(Camera *self, float radius)
{
  self->pos.x = 0.0f;
  self->pos.y = 0.0f;
  self->pos.z = radius;

  self->theta = 45.0f;
  self->phi   = 90.0f;

  self->radius = radius;
  self->zoom   = 45.0f;

  glm_vec3_copy(GLM_VEC3_ZERO, self->target.raw);

  Camera_update(self);
}

void Camera_update(Camera *self)
{
  self->theta = glm_clamp(self->theta, -89.0f, 89.0f);
  self->zoom = glm_clamp(self->zoom, 1.0f, 45.0f);

  self->pos.x =
      cos(glm_rad(self->phi)) * cos(glm_rad(self->theta)) * self->radius;
  self->pos.y = sin(glm_rad(self->theta)) * self->radius;
  self->pos.z =
      sin(glm_rad(self->phi)) * cos(glm_rad(self->theta)) * self->radius;
}

void Camera_getViewMatrix(Camera *self, mat4 dest)
{
  glm_lookat(self->pos.raw, self->target.raw, worldUp, dest);
}

void Camera_getProjectionMatrix(Camera *self, float aspectRatio, mat4 dest)
{
  glm_perspective(glm_rad(self->zoom), aspectRatio, 0.1f, 100.0f, dest);
}
