#pragma once

#include "game/ground.h"
#include "game/player.h"
#include "game/sword.h"
#include "game/tile.h"
#include "game/wall.h"

typedef struct {
  Camera camera;
  Player player;
  Sword  sword;

  Tiles  tiles;
  Ground ground;
  Wall   wall;
} Level;

void Level_init(Level *self, const char *path);
void Level_update(Level *self, float deltaTime);
void Level_draw(Level *self);
