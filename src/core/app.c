#include "app.h"
#include "window.h"
#include "input.h"

static Window window;

static void _draw(App *self);
static void _update(App *self);
static void _destroy(App *self);
static void _handleResizeWindow(GLFWwindow *handle, int width, int height);

// Public Functions
void App_init(App *self, FApp init, FApp update, FApp draw, FApp destroy)
{
  self->init    = init;
  self->update  = update;
  self->draw    = draw;
  self->destroy = destroy;

  Window_init(&window, (vec2s){.x = 900, .y = 600}, "Game");

  glfwSetFramebufferSizeCallback(window.handle, _handleResizeWindow);

  if (init != NULL)
    init();
}

void App_update(App *self)
{
  while (!glfwWindowShouldClose(window.handle)) {
    _update(self);
    _draw(self);
  }

  glfwTerminate();
}

void App_quit(App *self)
{
  _destroy(self);
}

float getAspectRatio()
{
  return window.size.x / window.size.y;
}

// Private Functions
static void _draw(App *self)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

  if (self->draw != NULL)
    self->draw();
}

static void _update(App *self)
{
  Keyboard_update(window.handle);
  if (self->update != NULL)
    self->update();

  glfwSwapBuffers(window.handle);
  glfwPollEvents();
}

static void _destroy(App *self)
{
  glfwSetWindowShouldClose(window.handle, true);

  if (self->destroy != NULL)
    self->destroy();
}

static void _handleResizeWindow(GLFWwindow *handle, int width, int height)
{
  window.size.x = width;
  window.size.y = height;
  glViewport(0, 0, window.size.x, window.size.y);
}
