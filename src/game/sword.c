#include "sword.h"
#include "GLFW/glfw3.h"

#include <cglm/vec3.h>

static bool _attacking = false;

static void _animateIdle(Sword *self, float deltaTime);

// Public functions
void Sword_init(Sword *self, vec3 pos)
{
  self->isHeld = false;

  Sprite_init(&self->sprite, "res/textures/Sword.png");
  glm_vec3_copy(pos, self->sprite.pos.raw);

  self->sprite.scale.x = 0.5f;
  self->sprite.scale.y = 0.5f;
}

void Sword_update(Sword *self, Player *player, float deltaTime)
{
  if (!self->isHeld) {
    _animateIdle(self, deltaTime);
  }
}

void Sword_draw(Sword *self, Camera *camera)
{
  Sprite_draw(&self->sprite, camera);
}

// Private functions
static void _animateIdle(Sword *self, float deltaTime)
{
  self->sprite.pos.y += sin(glfwGetTime() * 5.0f) * deltaTime;
  self->sprite.rotation.y =
      glm_lerp(self->sprite.rotation.y, self->sprite.rotation.y + 5.0f, 0.1f);
}
