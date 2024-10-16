#include "geometry.h"

#include <string.h>
#include <cglm/cglm.h>

void Geometry_init(Geometry *self)
{
  self->positions          = NULL;
  self->positionsCount     = 0;
  self->normals            = NULL;
  self->normalsCount       = 0;
  self->textureCoords      = NULL;
  self->textureCoordsCount = 0;
  self->indices            = NULL;
  self->indicesCount       = 0;
  glm_mat4_copy(GLM_MAT4_IDENTITY, self->model);
}

void Geometry_free(Geometry *self)
{
  free(self->positions);
  self->positions      = NULL;
  self->positionsCount = 0;
  free(self->normals);
  self->normals      = NULL;
  self->normalsCount = 0;
  free(self->textureCoords);
  self->textureCoords      = NULL;
  self->textureCoordsCount = 0;
  free(self->indices);
  self->indices      = NULL;
  self->indicesCount = 0;
}

void Geometry_setPositions(Geometry *self, float *positions,
                           size_t positionsCount)
{
  if (self->positions != NULL) {
    free(self->positions);
  }
  size_t size          = sizeof(float) * positionsCount;
  self->positions      = malloc(size);
  self->positionsCount = positionsCount;
  memcpy(self->positions, positions, size);
}

void Geometry_setNormals(Geometry *self, float *normals, size_t normalsCount)
{
  if (self->normals != NULL) {
    free(self->positions);
  }
  size_t size        = sizeof(float) * normalsCount;
  self->normals      = malloc(size);
  self->normalsCount = normalsCount;
  memcpy(self->normals, normals, size);
}

void Geometry_setTextureCoords(Geometry *self, float *textureCoords,
                               size_t textureCoordsCount)
{
  if (self->normals != NULL) {
    free(self->positions);
  }
  size_t size              = sizeof(float) * textureCoordsCount;
  self->textureCoords      = malloc(size);
  self->textureCoordsCount = textureCoordsCount;
  memcpy(self->textureCoords, textureCoords, size);
}

void Geometry_setIndices(Geometry *self, unsigned int *indices,
                         size_t indicesCount)
{
  if (self->indices != NULL) {
    free(self->indices);
  }
  size_t size        = sizeof(unsigned int) * indicesCount;
  self->indices      = malloc(size);
  self->indicesCount = indicesCount;
  memcpy(self->indices, indices, size);
}

float *Geometry_getVertices(Geometry *self)
{
  size_t length =
      self->positionsCount + self->normalsCount + self->textureCoordsCount;
  float *out = malloc(length * sizeof(float));
  for (size_t i = 0; i < length; i++) {
    out[i] = -2.0f;
  }

  size_t stride = 0;
  if (self->positionsCount > 0) {
    stride += 3;
  }
  if (self->normalsCount > 0) {
    stride += 3;
  }
  if (self->textureCoordsCount > 0) {
    stride += 2;
  }
  size_t offset = 0;
  if (self->positionsCount > 0) {
    size_t idx = 0;
    for (size_t i = offset; i < length; i += stride) {
      for (size_t j = 0; j < 3; j++) {
        out[i + j] = self->positions[idx++];
      }
    }
    offset += 3;
  }
  if (self->textureCoordsCount > 0) {
    size_t idx = 0;
    for (size_t i = offset; i < length; i += stride) {
      for (size_t j = 0; j < 2; j++) {
        out[i + j] = self->textureCoords[idx++];
      }
    }
    offset += 2;
  }
  if (self->normalsCount > 0) {
    size_t idx = 0;
    for (size_t i = offset; i < length; i += stride) {
      for (size_t j = 0; j < 3; j++) {
        out[i + j] = self->normals[idx++];
      }
    }
    offset += 3;
  }

  return out;
}

size_t Geometry_getVerticesCount(Geometry *self)
{
  return self->positionsCount + self->normalsCount + self->textureCoordsCount;
}

GBuffer Geometry_generateVbo(Geometry *self)
{
  float *vertices = Geometry_getVertices(self);

  GBuffer out;
  GBuffer_init(&out, GL_ARRAY_BUFFER, false);
  size_t size =
      (self->positionsCount + self->normalsCount + self->textureCoordsCount) *
      sizeof(float);
  GBuffer_data(&out, size, vertices);

  free(vertices);
  return out;
}

GBuffer Geometry_generateIbo(Geometry *self)
{
  GBuffer out;
  GBuffer_init(&out, GL_ELEMENT_ARRAY_BUFFER, false);
  GBuffer_data(&out, sizeof(unsigned int) * self->indicesCount, self->indices);

  return out;
}

void Geometry_setVaoAttribs(Geometry *self, GBuffer *vbo, Vao *vao)
{
  if (vbo->type != GL_ARRAY_BUFFER) {
    return;
  }

  size_t offset = 0;
  if (self->positionsCount > 0) {
    Vao_attribPointer(vao, vbo, 0, 3, GL_FLOAT, 0, 0);
    offset += self->positionsCount * sizeof(float);
  }
  if (self->normalsCount > 0) {
    Vao_attribPointer(vao, vbo, 1, 3, GL_FLOAT, 0, offset);
    offset += self->normalsCount * sizeof(float);
  }
  if (self->textureCoordsCount > 0) {
    Vao_attribPointer(vao, vbo, 2, 2, GL_FLOAT, 0, offset);
  }
}

void Geometry_translate(Geometry *self, vec3 value)
{
  glm_translate(self->model, value);
}

void Geometry_scale(Geometry *self, vec3 value)
{
  glm_scale(self->model, value);
}

void Geometry_rotate(Geometry *self, float angleDegrees, vec3 axis)
{
  glm_rotate(self->model, glm_rad(angleDegrees), axis);
}

void Geometry_rotateX(Geometry *self, float angleDegrees)
{
  glm_rotate(self->model, glm_rad(angleDegrees), (vec3){1.0f, 0.0f, 0.0f});
}

void Geometry_rotateY(Geometry *self, float angleDegrees)
{
  glm_rotate(self->model, glm_rad(angleDegrees), (vec3){0.0f, 1.0f, 0.0f});
}

void Geometry_rotateZ(Geometry *self, float angleDegrees)
{
  glm_rotate(self->model, glm_rad(angleDegrees), (vec3){0.0f, 0.0f, 1.0f});
}
