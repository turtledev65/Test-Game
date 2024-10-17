#include "sprite.h"

#include "core/app.h"
#include "gfx/gbuffer.h"
#include "gfx/geometry.h"
#include "gfx/shader.h"
#include "gfx/vao.h"
#include "util/array.h"

#include <cglm/cglm.h>

static Vao     _vao;
static GBuffer _vbo;
static GBuffer _ibo;
static Shader  _shader;
static bool    _initialized = false;

static void _init();

// Public Functions
void Sprite_init(Sprite *self, const char *path)
{
  _init();

  glm_vec3_copy(GLM_VEC3_ZERO, self->pos.raw);
  glm_vec3_copy(GLM_VEC3_ONE, self->scale.raw);
  glm_vec3_copy(GLM_VEC3_ZERO, self->rotation.raw);

  glActiveTexture(GL_TEXTURE0);
  Texture_init(&self->texture, path);
}

void Sprite_draw(Sprite *self, Camera *camera)
{
  Shader_use(&_shader);

  Shader_setInt(&_shader, "uTexture", 0);

  glActiveTexture(GL_TEXTURE0);
  Texture_bind(&self->texture);

  mat4 model = GLM_MAT4_IDENTITY_INIT;
  glm_translate(model, self->pos.raw);
  glm_rotate(model, glm_rad(self->rotation.z), (vec3){0.0f, 0.0f, 1.0f});
  glm_rotate(model, glm_rad(self->rotation.y), (vec3){0.0f, 1.0f, 0.0f});
  glm_rotate(model, glm_rad(self->rotation.x), (vec3){1.0f, 0.0f, 0.0f});
  glm_scale(model, self->scale.raw);
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

  float positions[]      = {-1.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.0f,
                            1.0f,  1.0f, 0.0f, 1.0f,  -1.0f, 0.0f};
  float textureCoords[]  = {0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f};
  unsigned int indices[] = {0, 1, 2, 1, 2, 3};

  Geometry geometry;
  Geometry_init(&geometry);
  Geometry_setPositions(&geometry, positions, LENGTH(positions));
  Geometry_setTextureCoords(&geometry, textureCoords, LENGTH(textureCoords));
  Geometry_setIndices(&geometry, indices, LENGTH(indices));

  _vbo = Geometry_generateVbo(&geometry);
  _ibo = Geometry_generateIbo(&geometry);
  Vao_init(&_vao);
  Geometry_setVaoAttribs(&geometry, &_vbo, &_vao);

  Geometry_free(&geometry);

  Shader_init(&_shader, "res/shaders/sprite.vert.glsl",
              "res/shaders/sprite.frag.glsl");
}
