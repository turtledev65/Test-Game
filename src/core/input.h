#pragma once

#include <GLFW/glfw3.h>
#include <stdbool.h>

typedef struct {
  bool down, lastDown;
} Key;

typedef struct {
  Key keys[GLFW_KEY_LAST];
} Keyboard;
extern Keyboard keyboard;

bool isKeyPressed(int key);
bool isKeyDown(int key);

void Keyboard_update(GLFWwindow *handle);
