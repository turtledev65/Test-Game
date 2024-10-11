#include "player.h"

#include "core/input.h"
#include "game/sprite.h"

#include <cglm/cglm.h>

#define ANIMATION_SPEED 10.0f;

void Player_init(Player *self, vec3 pos)
{
  Sprite_init(&self->sprite, "res/textures/player.png");
  glm_vec3_copy(pos, self->sprite.pos.raw);
  self->speed = 3.0f;
  self->sprite.scale.x = 0.5f;
  self->sprite.scale.y = 0.5f;
  self->sprite.scale.z = 0.5f;
}

void Player_update(Player *self, float deltaTime)
{
  vec3s dir = {.x = (isKeyDown(GLFW_KEY_D) || isKeyDown(GLFW_KEY_RIGHT)) -
                    (isKeyDown(GLFW_KEY_A) || isKeyDown(GLFW_KEY_LEFT)),
               .y = 0.0f,
               .z = (isKeyDown(GLFW_KEY_S) || isKeyDown(GLFW_KEY_DOWN)) -
                    (isKeyDown(GLFW_KEY_W) || isKeyDown(GLFW_KEY_UP))};
  glm_vec3_normalize(dir.raw);

  float t = 0.0f;
  if (dir.x != 0.0f) {
    t = self->sprite.pos.x;
  } else if (dir.z != 0.0f) {
    t = self->sprite.pos.z;
  }
  t *= ANIMATION_SPEED;

  self->sprite.pos.x += dir.x * deltaTime * self->speed;
  self->sprite.pos.z += dir.z * deltaTime * self->speed;
  self->sprite.pos.y += sin(t) * deltaTime;
  self->sprite.pos.y = glm_max(self->sprite.pos.y, 0.0f);
}

void Player_draw(Player *self, Camera *camera)
{
  Sprite_draw(&self->sprite, camera);
}
