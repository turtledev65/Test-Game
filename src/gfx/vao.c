#include "vao.h"

#include <glad/glad.h>
#include <stdio.h>

void Vao_init(Vao *self)
{
  glGenVertexArrays(1, &self->handle);
}

void Vao_destroy(Vao *self)
{
  glDeleteVertexArrays(1, &self->handle);
}

void Vao_bind(Vao *self)
{
  glBindVertexArray(self->handle);
}

void Vao_attribPointer(Vao *self, GBuffer *vbo, unsigned int index, int size,
                       GLenum type, int stride, size_t offset)
{
  if (vbo->type != GL_ARRAY_BUFFER) {
    fprintf(stderr, "ERROR: Buffer is not a vertex buffer");
    return;
  }

  Vao_bind(self);
  GBuffer_bind(vbo);

  glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void *)offset);
  glEnableVertexAttribArray(index);
}
