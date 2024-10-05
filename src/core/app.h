#pragma once

#include <stdbool.h>

typedef void (*FApp)();

typedef struct {
  FApp init, update, draw, destroy;
} App;

void  App_init(App *self, FApp init, FApp update, FApp draw, FApp destroy);
void  App_update(App *self);
void  App_quit(App *self);

float getAspectRatio();

bool isKeyPressed(int key);
bool isKeyDown(int key);
