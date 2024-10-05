#include "texture.h"

#include <stdbool.h>
#include <stb_image.h>

void Texture_init(Texture *self, GLenum format, const char *path)
{
  stbi_set_flip_vertically_on_load(true);

  int            width, height;
  int            nrChannels;
  unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

  if (data != NULL) {
    Texture_initFromData(self, width, height, format, data);
  } else {
    fprintf(stderr, "ERROR: Failed to load texture %s: %s\n", path,
            stbi_failure_reason());
  }

  stbi_image_free(data);
}

void Texture_initFromData(Texture *self, size_t width, size_t height,
                          GLenum format, void *data)
{
  glGenTextures(1, &self->handle);
  Texture_bind(self);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture_bind(Texture *self)
{
  glBindTexture(GL_TEXTURE_2D, self->handle);
}

void Texture_destroy(Texture *self)
{
  glDeleteTextures(1, &self->handle);
}
