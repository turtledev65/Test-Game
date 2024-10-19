#include "camera.h"

#include "cglm/cam.h"

static vec3 worldUp = {0.0f, 1.0f, 0.0f};

void Camera_init(Camera *self)
{
  self->radius = 14.0f;
  self->zoom   = 45.0f;

  self->pos.x = 0.0f;
  self->pos.y = 0.0f;
  self->pos.z = self->radius;

  self->theta = 40.0f;
  self->phi   = 90.0f;

  glm_vec3_copy(GLM_VEC3_ZERO, self->target.raw);

  Camera_update(self);
}

void Camera_update(Camera *self)
{
  self->theta = glm_clamp(self->theta, -89.0f, 89.0f);
  self->zoom  = glm_clamp(self->zoom, 1.0f, 45.0f);

  vec3s dir = {.x = cos(glm_rad(self->phi)) * cos(glm_rad(self->theta)),
               .y = sin(glm_rad(self->theta)),
               .z = sin(glm_rad(self->phi)) * cos(glm_rad(self->theta))};
  glm_vec3_scale(dir.raw, self->radius, dir.raw);
  glm_vec3_add(self->target.raw, dir.raw, self->pos.raw);
}

void Camera_getViewMatrix(Camera *self, mat4 dest)
{
  glm_lookat(self->pos.raw, self->target.raw, worldUp, dest);
}

void Camera_getProjectionMatrix(Camera *self, float aspectRatio, mat4 dest)
{
  glm_perspective(glm_rad(self->zoom), aspectRatio, 0.1f, 100.0f, dest);
}
