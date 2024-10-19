#pragma once

#include "game/player.h"
#include "game/sprite.h"

#include <stdbool.h>

typedef struct {
  Sprite sprite;
  bool   isHeld;
} Sword;

void Sword_init(Sword *self, vec3 pos);
void Sword_update(Sword *self, Player *player, float deltaTime);
void Sword_draw(Sword *self, Camera *camera);
