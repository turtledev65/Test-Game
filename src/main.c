#include <stdlib.h>
#include <stdio.h>

#include "game/camera.h"
#include "game/sprite.h"

#include "core/app.h"
#include "core/input.h"

static App app;

static Sprite container;
static Sprite face;
static Camera camera;

static void init()
{
  Camera_init(&camera, 5.0f);

  Sprite_init(&container, GL_RGB, "res/textures/container.jpg");
  container.pos.z = -2.0f;
  container.pos.y = -1.0f;

  Sprite_init(&face, GL_RGBA, "res/textures/awesomeface.png");
}

static void draw()
{
  Sprite_draw(&container, &camera);
  Sprite_draw(&face, &camera);
}

static void update()
{
  if (isKeyDown(GLFW_KEY_ESCAPE)) {
    App_quit(&app);
  }

  Camera_update(&camera);
}

int main()
{
  App_init(&app, init, update, draw, NULL);
  App_update(&app);
}
