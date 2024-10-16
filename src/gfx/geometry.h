#pragma once

#include <stdlib.h>
#include <cglm/types.h>

#include "gfx/gbuffer.h"
#include "gfx/vao.h"

typedef struct {
  // positions of vertices (x, y ,z)
  float *positions;
  size_t positionsCount;
  // normals (x, y, z)
  float *normals;
  size_t normalsCount;
  // texture coordinates (x, y)
  float *textureCoords;
  size_t textureCoordsCount;
  // indices if you want to use an index buffer
  unsigned int *indices;
  size_t        indicesCount;

  mat4 model;
} Geometry;

void Geometry_init(Geometry *self);
void Geometry_free(Geometry *self);

void Geometry_setPositions(Geometry *self, float *positions,
                           size_t positionsCount);
void Geometry_setNormals(Geometry *self, float *normals, size_t normalsCount);
void Geometry_setTextureCoords(Geometry *self, float *textureCoords,
                               size_t textureCoordsCount);
void Geometry_setIndices(Geometry *self, unsigned int *indices,
                         size_t indicesCount);
void Geometry_setVaoAttribs(Geometry *self, GBuffer *vbo, Vao *vao);

float *Geometry_getVertices(Geometry *self);
size_t Geometry_getVerticesCount(Geometry *self);

GBuffer Geometry_generateVbo(Geometry *self);
GBuffer Geometry_generateIbo(Geometry *self);

void Geometry_translate(Geometry *self, vec3 value);
void Geometry_scale(Geometry *self, vec3 value);
void Geometry_rotate(Geometry *self, float angleDegrees, vec3 axis);
void Geometry_rotateX(Geometry *self, float angleDegrees);
void Geometry_rotateY(Geometry *self, float angleDegrees);
void Geometry_rotateZ(Geometry *self, float angleDegrees);
