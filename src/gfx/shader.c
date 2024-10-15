#include "shader.h"
#include "util/file.h"

#include <stdlib.h>
#include <stdio.h>

#include <glad/glad.h>

static unsigned int _compileShader(GLenum type, const char *source);
static unsigned int _linkProgram(unsigned int vertexShader,
                                 unsigned int fragmentShader);

// Pulbic Functions
void Shader_init(Shader *self, const char *vsPath, const char *fsPath)
{
  char *vsSource = readFile(vsPath);
  char *fsSource = readFile(fsPath);
  if (vsSource != NULL && fsSource != NULL)
    Shader_initWithSource(self, vsSource, fsSource);

  free(vsSource);
  free(fsSource);
}

void Shader_initWithSource(Shader *self, const char *vsSource,
                           const char *fsSource)
{
  self->vsHandle = _compileShader(GL_VERTEX_SHADER, vsSource);
  self->fsHandle = _compileShader(GL_FRAGMENT_SHADER, fsSource);
  self->handle   = _linkProgram(self->vsHandle, self->fsHandle);
}

void Shader_use(Shader *self)
{
  glUseProgram(self->handle);
}

void Shader_setInt(Shader *self, const char *name, int val)
{
  glUniform1i(glGetUniformLocation(self->handle, name), val);
}

void Shader_setFloat(Shader *self, const char *name, float val)
{
  glUniform1f(glGetUniformLocation(self->handle, name), val);
}

void Shader_setVec3(Shader *self, const char *name, float *val)
{
  glUniform3fv(glGetUniformLocation(self->handle, name), 1, val);
}

void shader_setVec3XYZ(Shader *self, const char *name, float x, float y,
                       float z)
{
  glUniform3f(glGetUniformLocation(self->handle, name), x, y, z);
}

void Shader_setMat4(Shader *self, const char *name, mat4 val)
{
  glUniformMatrix4fv(glGetUniformLocation(self->handle, name), 1, GL_FALSE,
                     val[0]);
}

// Priate Functions
static unsigned int _compileShader(GLenum type, const char *source)
{
  unsigned int shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infoLog[1024];
    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
    fprintf(stderr, "Failed to compile %s shader:\n%s\n",
            type == GL_VERTEX_SHADER ? "vertex" : "fragment", infoLog);
  }

  return shader;
}

static unsigned int _linkProgram(unsigned int vertexShader,
                                 unsigned int fragmentShader)
{
  unsigned int program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  int success;
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    char infoLog[1024];
    glGetProgramInfoLog(program, 1024, NULL, infoLog);
    fprintf(stderr, "Failed to link shader program:\n%s\n", infoLog);
  }

  return program;
}
