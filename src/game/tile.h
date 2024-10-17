#pragma once

#include <stdlib.h>

#include "util/dynamic-array.h"

typedef enum {
  TILE_GROUND = 0,
  TILE_WALL,
} TileType;

typedef struct {
  union {
    size_t col;
    size_t x;
  };
  union {
    size_t row;
    size_t z;
  };
  TileType type;
} Tile;

typedef DYN_ARR(Tile) Tiles;
