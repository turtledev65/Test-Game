#include "instanced-mesh.h"
#include "core/app.h"

#include <cglm/mat4.h>
#include <stdlib.h>

void InstancedMesh_init(InstancedMesh *self, Geometry *geometry,
                        vec3 instanceColor, size_t count)
{
  self->count    = count;
  self->geometry = *geometry;
  glm_vec3_copy(instanceColor, self->instanceColor);

  self->vbo = Geometry_generateVbo(geometry);
  if (geometry->indicesCount > 0) {
    self->ibo = Geometry_generateIbo(geometry);
  }

  Vao_init(&self->vao);
  Geometry_setVaoAttribs(geometry, &self->vbo, &self->vao);

  // Set the instance matrices
  self->modelMatrices = calloc(count, sizeof(mat4));

  Shader_init(&self->shader, "res/shaders/instanced.vert.glsl",
              "res/shaders/instanced.frag.glsl");
}

void InstancedMesh_setTexture(InstancedMesh *self, Texture *texture)
{
  if (self->hasTexture) {
    Texture_destroy(&self->texture);
  }
  self->texture    = *texture;
  self->hasTexture = true;
}

void InstancedMesh_setMatrixAt(InstancedMesh *self, size_t i, mat4 matrix)
{
  if (i >= self->count) {
    return;
  }

  glm_mat4_copy(matrix, self->modelMatrices[i]);
}

void InstancedMesh_sendModelMatrices(InstancedMesh *self)
{
  GBuffer buffer;
  GBuffer_init(&buffer, GL_ARRAY_BUFFER, false);
  GBuffer_data(&buffer, self->count * sizeof(mat4), &self->modelMatrices[0]);
  Vao_attribPointer(&self->vao, &buffer, 3, 4, GL_FLOAT, sizeof(mat4), 0);
  Vao_attribPointer(&self->vao, &buffer, 4, 4, GL_FLOAT, sizeof(mat4),
                    1 * sizeof(vec4));
  Vao_attribPointer(&self->vao, &buffer, 5, 4, GL_FLOAT, sizeof(mat4),
                    2 * sizeof(vec4));
  Vao_attribPointer(&self->vao, &buffer, 6, 4, GL_FLOAT, sizeof(mat4),
                    3 * sizeof(vec4));
  glVertexAttribDivisor(3, 1);
  glVertexAttribDivisor(4, 1);
  glVertexAttribDivisor(5, 1);
  glVertexAttribDivisor(6, 1);
  glBindVertexArray(0);
  GBuffer_delete(&buffer);
}

void InstancedMesh_draw(InstancedMesh *self, Camera *camera)
{
  Shader_use(&self->shader);

  if (self->hasTexture) {
    glActiveTexture(GL_TEXTURE0);
    Texture_bind(&self->texture);
  }

  Shader_setVec3(&self->shader, "uColor", self->instanceColor);

  mat4 view;
  Camera_getViewMatrix(camera, view);
  Shader_setMat4(&self->shader, "uView", view);

  mat4 proj;
  Camera_getProjectionMatrix(camera, getAspectRatio(), proj);
  Shader_setMat4(&self->shader, "uProj", proj);

  Vao_bind(&self->vao);
  GBuffer_bind(&self->vbo);

  if (self->geometry.indicesCount > 0) {
    GBuffer_bind(&self->ibo);
    glDrawElementsInstanced(GL_TRIANGLES, self->geometry.indicesCount,
                            GL_UNSIGNED_INT, NULL, self->count);
  } else {
    glDrawArraysInstanced(GL_TRIANGLES, 0,
                          Geometry_getVerticesCount(&self->geometry),
                          self->count);
  }
}
