#pragma once

#include "gbuffer.h"

typedef struct {
  unsigned int handle;
} Vao;

void Vao_init(Vao *self);
void Vao_destroy(Vao *self);
void Vao_bind(Vao *self);
void Vao_attribPointer(Vao *self, GBuffer *vbo, unsigned int index, int size,
                       GLenum type, int stride, size_t offset);
