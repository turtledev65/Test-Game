#include <stdlib.h>
#include <stdio.h>

#include "game/camera.h"
#include "game/plane.h"
#include "game/player.h"
#include "game/sprite.h"

#include "core/app.h"
#include "core/input.h"

#include <cglm/cglm.h>

static App app;

static Camera camera;

static Sprite container;
static Plane  plane;
static Player player;

static void init()
{
  Camera_init(&camera);

  Sprite_init(&container, "res/textures/container.jpg");
  container.pos.z      = -4.0f;
  container.pos.y      = -1.0f;
  container.rotation.x = -90.0f;

  Plane_init(&plane, (vec3s){.x = 0.0f, .y = -1.0f, .z = 0.0f},
             (vec3s){.x = 2.0f, .y = 2.0f});
  Player_init(&player, GLM_VEC3_ZERO);
}

static void update(float deltaTime)
{
  if (isKeyDown(GLFW_KEY_ESCAPE)) {
    App_quit(&app);
  }

  Camera_update(&camera);
  Player_update(&player, deltaTime);

  // Update the target to the player's position
  vec3s target = {
      .x = player.sprite.pos.x,
      .y = 0.0f, // don't follow the player's y position
      .z = player.sprite.pos.z,
  };
  glm_vec3_lerp(camera.target.raw, target.raw, 0.05f, camera.target.raw);
}

static void draw(float deltaTime)
{
  Sprite_draw(&container, &camera);
  Plane_draw(&plane, &camera);
  Player_draw(&player, &camera);
}

int main()
{
  App_init(&app, init, update, draw, NULL);
  App_update(&app);
}
