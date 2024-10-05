#include "sprite.h"

#include "core/app.h"

#include "gfx/gbuffer.h"
#include "gfx/shader.h"
#include "gfx/vao.h"

#include <cglm/cglm.h>

static Vao     _vao;
static GBuffer _vbo;
static GBuffer _ibo;
static Shader  _shader;
static bool    _initialized = false;

static void _init();

// Public Functions
void Sprite_init(Sprite *self, GLenum format, const char *path)
{
  _init();

  glm_vec3_copy(GLM_VEC3_ZERO, self->pos.raw);

  glActiveTexture(GL_TEXTURE0);
  Texture_init(&self->texture, format, path);
}

void Sprite_draw(Sprite *self, Camera *camera)
{
  Shader_use(&_shader);

  Shader_setInt(&_shader, "uTexture", 0);

  glActiveTexture(GL_TEXTURE0);
  Texture_bind(&self->texture);

  mat4 model = GLM_MAT4_IDENTITY_INIT;
  glm_translate(model, self->pos.raw);
  Shader_setMat4(&_shader, "uModel", model);

  mat4 view;
  Camera_getViewMatrix(camera, view);
  Shader_setMat4(&_shader, "uView", view);

  mat4 proj;
  Camera_getProjectionMatrix(camera, getAspectRatio(), proj);
  Shader_setMat4(&_shader, "uProj", proj);

  Vao_bind(&_vao);
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
      // position         // texture coords
      -1.0f, 1.0f,  0.0f, 0.0f, 1.0f, // top left
      -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom left
      1.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top right
      1.0f,  -1.0f, 0.0f, 1.0f, 0.0f, // bottom right
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
  Vao_attribPointer(&_vao, &_vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), 0);
  Vao_attribPointer(&_vao, &_vbo, 1, 2, GL_FLOAT, 5 * sizeof(float),
                    3 * sizeof(float));

  Shader_init(&_shader, "res/shaders/base.vert.glsl",
              "res/shaders/base.frag.glsl");
}
