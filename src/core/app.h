#pragma once

#include <stdbool.h>

typedef struct {
  void (*init)();
  void (*destroy)();
  void (*update)(float deltaTime);
  void (*draw)(float deltaTime);
} App;

void App_init(App *self, void (*init)(), void (*update)(float deltaTime),
              void (*draw)(float deltaTime), void (*destroy)());
void App_update(App *self);
void App_quit(App *self);

float getAspectRatio();

bool isKeyPressed(int key);
bool isKeyDown(int key);
