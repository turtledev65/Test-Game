#pragma once

#include <stdlib.h>
#include <glad/glad.h>

typedef struct {
  unsigned int handle;
} Texture;

void Texture_init(Texture *self, const char *path);
void Texture_initFromData(Texture *self, size_t width, size_t height,
                          GLenum format, void *data);
void Texture_bind(Texture *self);
void Texture_destroy(Texture *self);
