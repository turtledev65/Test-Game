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

typedef struct {
  bool down, lastDown;
} MouseButton;

typedef struct {
  MouseButton buttons[GLFW_MOUSE_BUTTON_LAST];
} Mouse;
extern Mouse mouse;

bool isMouseButtonPressed(int button);
bool isMouseButtonDown(int button);
void Mouse_update(GLFWwindow *handle);
