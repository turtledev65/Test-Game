#pragma once

#include "gfx/gbuffer.h"
#include "gfx/shader.h"
#include "gfx/vao.h"

#include "game/camera.h"

typedef struct {
  size_t count;
  size_t indicesCount;

  vec3s color;

  Shader  shader;
  Vao     vao;
  GBuffer vbo;
  GBuffer ibo;
} InstancedMesh;

void InstancedMesh_init(InstancedMesh *self, size_t count, mat4 *modelMatrices,
                        float *vertices, size_t verticesCount,
                        unsigned int *indices, size_t indicesCount, vec3 color);
void InstancedMesh_draw(InstancedMesh *self, Camera *camera);
