#include "file.h"

#include <stdio.h>
#include <stdlib.h>

char *readFile(const char *path)
{
  FILE *file = fopen(path, "rb");
  if (file == NULL) {
    fprintf(stderr, "Failed to find file %s\n", path);
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  rewind(file);

  char *out = malloc(size + 1);
  fread(out, 1, size, file);
  out[size] = '\0';

  fclose(file);
  return out;
}
