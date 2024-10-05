#include "gbuffer.h"

void GBuffer_init(GBuffer *self, GLenum type, bool dynamic)
{
  glGenBuffers(1, &self->handle);
  self->type    = type;
  self->dynamic = dynamic;
}

void GBuffer_delete(GBuffer *self)
{
  glDeleteBuffers(1, &self->handle);
}

void GBuffer_bind(GBuffer *self)
{
  glBindBuffer(self->type, self->handle);
}

void GBuffer_data(GBuffer *self, size_t size, void *data)
{
  GBuffer_bind(self);
  glBufferData(self->type, size, data,
               self->dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}
