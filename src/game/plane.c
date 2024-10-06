#include "plane.h"

#include <stdbool.h>

#include <cglm/cglm.h>
#include <cglm/vec3.h>
#include <cglm/mat4.h>

#include "core/app.h"
#include "gfx/shader.h"
#include "gfx/vao.h"

static Shader  _shader;
static Vao     _vao;
static GBuffer _vbo;
static GBuffer _ibo;
static bool    _initialized = false;

static void _init();

// Public Functions
void Plane_init(Plane *self, vec3s pos, vec3s scale)
{
  _init();

  glm_vec3_copy(pos.raw, self->pos.raw);
  glm_vec3_copy(scale.raw, self->scale.raw);
  glm_vec3_copy((vec3){0.47f, 0.24f, 0.24f}, self->color.raw);
}

void Plane_draw(Plane *self, Camera *camera)
{
  Shader_use(&_shader);
  Shader_setVec3(&_shader, "uColor", self->color.raw);

  mat4 model = GLM_MAT4_IDENTITY_INIT;
  glm_translate(model, self->pos.raw);
  glm_rotate(model, glm_rad(90.0f), (vec3){1.0f, 0.0f, 0.0f});
  glm_scale(model, self->scale.raw);
  Shader_setMat4(&_shader, "uModel", model);

  mat4 view;
  Camera_getViewMatrix(camera, view);
  Shader_setMat4(&_shader, "uView", view);

  mat4 proj;
  Camera_getProjectionMatrix(camera, getAspectRatio(), proj);
  Shader_setMat4(&_shader, "uProj", proj);

  Vao_init(&_vao);
  GBuffer_bind(&_vbo);
  GBuffer_bind(&_ibo);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}

// Private Functions
static void _init()
{
  if (_initialized) {
    return;
  }

  _initialized = true;

  float vertices[] = {
      // position
      -1.0f, 1.0f,  0.0f, // top left
      -1.0f, -1.0f, 0.0f, // bottom left
      1.0f,  1.0f,  0.0f, // top right
      1.0f,  -1.0f, 0.0f, // bottom right
  };
  GBuffer_init(&_vbo, GL_ARRAY_BUFFER, false);
  GBuffer_data(&_vbo, sizeof(vertices), vertices);

  unsigned int indices[] = {
      0, 1, 2, // First Triagnle
      1, 2, 3  // Second Triangle
  };
  GBuffer_init(&_ibo, GL_ELEMENT_ARRAY_BUFFER, false);
  GBuffer_data(&_ibo, sizeof(indices), indices);

  Vao_init(&_vao);
  Vao_attribPointer(&_vao, &_vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), 0);

  Shader_init(&_shader, "res/shaders/color.vert.glsl",
              "res/shaders/color.frag.glsl");
}
