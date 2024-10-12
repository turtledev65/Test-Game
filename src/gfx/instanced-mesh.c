#include "instanced-mesh.h"
#include "core/app.h"

#include <cglm/mat4.h>
#include <stdlib.h>

void InstancedMesh_init(InstancedMesh *self, size_t count, mat4 *modelMatrices,
                        float *vertices, size_t verticesCount,
                        unsigned int *indices, size_t indicesCount, vec3 color)
{
  self->count         = count;
  self->verticesCount = verticesCount;
  self->indicesCount  = indicesCount;
  glm_vec3_copy(color, self->color.raw);

  // Init vbo
  GBuffer_init(&self->vbo, GL_ARRAY_BUFFER, false);
  GBuffer_data(&self->vbo, verticesCount * sizeof(float), vertices);

  // Init ibo
  if (indices != NULL) {
    GBuffer_init(&self->ibo, GL_ELEMENT_ARRAY_BUFFER, false);
    GBuffer_data(&self->ibo, indicesCount * sizeof(unsigned int), indices);
  }

  // Set the vertex attribs
  Vao_init(&self->vao);
  Vao_attribPointer(&self->vao, &self->vbo, 0, 3, GL_FLOAT, 3 * sizeof(float),
                    0);

  // Set the instance matrices
  GBuffer buffer;
  GBuffer_init(&buffer, GL_ARRAY_BUFFER, false);
  GBuffer_data(&buffer, count * sizeof(mat4), &modelMatrices[0]);
  Vao_attribPointer(&self->vao, &buffer, 1, 4, GL_FLOAT, sizeof(mat4), 0);
  Vao_attribPointer(&self->vao, &buffer, 2, 4, GL_FLOAT, sizeof(mat4),
                    1 * sizeof(vec4));
  Vao_attribPointer(&self->vao, &buffer, 3, 4, GL_FLOAT, sizeof(mat4),
                    2 * sizeof(vec4));
  Vao_attribPointer(&self->vao, &buffer, 4, 4, GL_FLOAT, sizeof(mat4),
                    3 * sizeof(vec4));
  glVertexAttribDivisor(1, 1);
  glVertexAttribDivisor(2, 1);
  glVertexAttribDivisor(3, 1);
  glVertexAttribDivisor(4, 1);
  glBindVertexArray(0);

  Shader_init(&self->shader, "res/shaders/instanced.vert.glsl",
              "res/shaders/instanced.frag.glsl");
}

void InstancedMesh_draw(InstancedMesh *self, Camera *camera)
{
  Shader_use(&self->shader);

  Shader_setVec3(&self->shader, "uColor", self->color.raw);

  mat4 view;
  Camera_getViewMatrix(camera, view);
  Shader_setMat4(&self->shader, "uView", view);

  mat4 proj;
  Camera_getProjectionMatrix(camera, getAspectRatio(), proj);
  Shader_setMat4(&self->shader, "uProj", proj);

  Vao_bind(&self->vao);
  GBuffer_bind(&self->vbo);
  if (self->indicesCount != 0) {
    GBuffer_bind(&self->ibo);
    glDrawElementsInstanced(GL_TRIANGLES, self->indicesCount, GL_UNSIGNED_INT,
                            NULL, self->count);
  } else {
    glDrawArraysInstanced(GL_TRIANGLES, 0, self->verticesCount, self->count);
  }
}
