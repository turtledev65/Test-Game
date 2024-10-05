#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include <glad/glad.h>

typedef struct {
  unsigned int handle;
  GLenum       type;
  bool         dynamic;
} GBuffer;

void GBuffer_init(GBuffer *self, GLenum type, bool dynamic);
void GBuffer_delete(GBuffer *self);
void GBuffer_bind(GBuffer *self);
void GBuffer_data(GBuffer *self, size_t size, void *data);
