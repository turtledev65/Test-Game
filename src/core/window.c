#include "window.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Window_init(Window *self, vec2s size, char *title)
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

#ifdef __linux__
  glfwWindowHintString(GLFW_X11_CLASS_NAME, "float");
  glfwWindowHintString(GLFW_X11_INSTANCE_NAME, "float");
#endif

  self->size = size;

  size_t len  = strlen(title);
  self->title = malloc(len);
  strncpy(self->title, title, len);

  self->handle =
      glfwCreateWindow(self->size.x, self->size.y, self->title, NULL, NULL);
  if (self->handle == NULL) {
    fprintf(stderr, "ERROR: Failed to create GLFW window!\n");
    exit(1);
  }
  glfwMakeContextCurrent(self->handle);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fprintf(stderr, "ERROR: Failed to init glad");
    exit(1);
  }

  glViewport(0, 0, self->size.x, self->size.y);

}
