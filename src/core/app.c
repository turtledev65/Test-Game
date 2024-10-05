#include "app.h"
#include "window.h"
#include "input.h"

static Window window;

static void _draw(App *self, float deltaTime);
static void _update(App *self, float deltaTime);
static void _destroy(App *self);
static void _handleResizeWindow(GLFWwindow *handle, int width, int height);

static float _prevTime = 0.0f;

// Public Functions
void App_init(App *self, void (*init)(), void (*update)(float deltaTime),
              void (*draw)(float deltaTime), void (*destroy)())
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
    float currTime  = glfwGetTime();
    float deltaTime = currTime - _prevTime;
    _prevTime       = currTime;

    _update(self, deltaTime);
    _draw(self, deltaTime);
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
static void _draw(App *self, float deltaTime)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

  if (self->draw != NULL)
    self->draw(deltaTime);
}

static void _update(App *self, float deltaTime)
{

  Keyboard_update(window.handle);
  if (self->update != NULL)
    self->update(deltaTime);

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
