#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/struct.h>

typedef struct {
  GLFWwindow *handle;
  vec2s       size;
  char       *title;
} Window;

void Window_init(Window *self, vec2s size, char *title);
