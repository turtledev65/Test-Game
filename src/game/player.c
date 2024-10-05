#include "player.h"

#include "core/input.h"
#include "game/sprite.h"

#include <cglm/cglm.h>

void Player_init(Player *self, vec3 pos)
{
  Sprite_init(&self->sprite, GL_RGBA, "res/textures/awesomeface.png");
  glm_vec3_copy(pos, self->sprite.pos.raw);
  self->speed = 3.0f;
}

void Player_update(Player *self, float deltaTime)
{
  vec3s dir = {.x = isKeyDown(GLFW_KEY_D) - isKeyDown(GLFW_KEY_A),
               .y = 0.0f,
               .z = isKeyDown(GLFW_KEY_S) - isKeyDown(GLFW_KEY_W)};
  glm_vec3_normalize(dir.raw);

  self->sprite.pos.x += dir.x * deltaTime * self->speed;
  self->sprite.pos.z += dir.z * deltaTime * self->speed;
}

void Player_draw(Player *self, Camera *camera)
{
  Sprite_draw(&self->sprite, camera);
}
