#include "player.h"

#include "core/input.h"
#include "game/sprite.h"

#include <cglm/cglm.h>

#define WALKING_SPEED 3.0f
#define GRAVITY 32.0f

#define ANIMATION_SPEED 8.0f

static bool _isOnGround(Player *self);

// Public Functions
void Player_init(Player *self, vec3 pos)
{
  Sprite_init(&self->sprite, "res/textures/player.png");
  glm_vec3_copy(pos, self->sprite.pos.raw);
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

  // Movement
  self->vel.x = dir.x * WALKING_SPEED;
  self->vel.z = dir.z * WALKING_SPEED;

  self->sprite.pos.x += self->vel.x * deltaTime;
  self->sprite.pos.y += self->vel.y * deltaTime;
  self->sprite.pos.z += self->vel.z * deltaTime;

  if (self->sprite.pos.y < 0.0f) {
    self->sprite.pos.y = 0.0f;
    self->vel.y        = 0.0f;
  }

  // Jumping
  if (isKeyPressed(GLFW_KEY_SPACE) && _isOnGround(self)) {
    self->vel.y += 10.0f;
  }

  // Animation
  if (_isOnGround(self)) {
    float t = 0.0f;
    if (dir.x != 0.0f) {
      t = self->sprite.pos.x;
    } else if (dir.z != 0.0f) {
      t = self->sprite.pos.z;
    }
    t *= ANIMATION_SPEED;
    self->sprite.pos.y += sin(t) * deltaTime;
    self->sprite.pos.y = glm_max(self->sprite.pos.y, 0.0f);
  } else {
    // Gravity
    self->vel.y -= GRAVITY * deltaTime;
  }
}

void Player_draw(Player *self, Camera *camera)
{
  Sprite_draw(&self->sprite, camera);
}

// Private functions
static bool _isOnGround(Player *self)
{
  return self->vel.y == 0.0f;
}
