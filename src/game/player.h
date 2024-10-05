#pragma once

#include "game/sprite.h"

typedef struct {
  Sprite sprite;
  float speed;
} Player;

void Player_init(Player *self, vec3 pos);
void Player_draw(Player *self, Camera *camera);
void Player_update(Player *self, float deltaTime);
