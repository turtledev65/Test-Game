#pragma once

#include "cglm/types.h"

typedef struct {
  unsigned int handle;
  unsigned int vsHandle, fsHandle;
} Shader;

void Shader_init(Shader *self, const char *vsPath, const char *fsPath);
void Shader_initWithSource(Shader *self, const char *vsSource,
                           const char *fsSource);
void Shader_use(Shader *self);

void Shader_setInt(Shader *self, const char *name, int val);
void Shader_setFloat(Shader *self, const char *name, float val);
void Shader_setVec3(Shader *self, const char *name, float *val);
void Shader_setMat4(Shader *self, const char *name, mat4 val);
