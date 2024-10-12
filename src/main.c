#include <stdlib.h>
#include <stdio.h>

#include "game/level.h"

#include "core/app.h"
#include "core/input.h"

static App   app;
static Level level;

InstancedMesh mesh;

static void init()
{
  Level_init(&level, "res/levels/test.level");
}

static void update(float deltaTime)
{
  if (isKeyDown(GLFW_KEY_ESCAPE)) {
    App_quit(&app);
  }

  Level_update(&level, deltaTime);
}

static void draw(float deltaTime)
{
  InstancedMesh_draw(&mesh, &level.camera);
  Level_draw(&level);
}

int main()
{
  App_init(&app, init, update, draw, NULL);
  App_update(&app);
}
