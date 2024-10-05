#include <stdlib.h>
#include <stdio.h>

#include "game/camera.h"
#include "game/player.h"
#include "game/sprite.h"

#include "core/app.h"
#include "core/input.h"

#include <cglm/cglm.h>

static App app;

static Camera camera;

static Sprite container;
static Player player;

static void init()
{
  Camera_init(&camera, 5.0f);

  Sprite_init(&container, GL_RGB, "res/textures/container.jpg");
  container.pos.z = -2.0f;
  container.pos.y = -1.0f;

  Player_init(&player, GLM_VEC3_ZERO);
}

static void update(float deltaTime)
{
  if (isKeyDown(GLFW_KEY_ESCAPE)) {
    App_quit(&app);
  }

  Camera_update(&camera);
  Player_update(&player, deltaTime);
}

static void draw(float deltaTime)
{
  Sprite_draw(&container, &camera);
  Player_draw(&player, &camera);
}

int main()
{
  App_init(&app, init, update, draw, NULL);
  App_update(&app);
}
