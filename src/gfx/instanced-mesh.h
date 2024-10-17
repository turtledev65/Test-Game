#pragma once

#include "gfx/gbuffer.h"
#include "gfx/shader.h"
#include "gfx/texture.h"
#include "gfx/vao.h"
#include "gfx/geometry.h"

#include "game/camera.h"

typedef struct {
  size_t   count;
  Geometry geometry;
  vec3     instanceColor;
  mat4    *modelMatrices;

  bool    hasTexture;
  Texture texture;

  bool _initialized;

  Shader  shader;
  Vao     vao;
  GBuffer vbo;
  GBuffer ibo;
} InstancedMesh;

void InstancedMesh_init(InstancedMesh *self, Geometry *geometry,
                        vec3 instanceColor, size_t count);
void InstancedMesh_draw(InstancedMesh *self, Camera *camera);

void InstancedMesh_setMatrixAt(InstancedMesh *self, size_t i, mat4 matrix);
void InstancedMesh_setTexture(InstancedMesh *self, Texture *texture);
void InstancedMesh_sendModelMatrices(InstancedMesh *self);
