#include "input.h"

Keyboard keyboard;

bool isKeyPressed(int key)
{
  return keyboard.keys[key].down && !keyboard.keys[key].lastDown;
}

bool isKeyDown(int key)
{
  return keyboard.keys[key].down;
}

void Keyboard_update(GLFWwindow *handle)
{
  // 32 is the first key
  for (int i = 32; i < GLFW_KEY_LAST; i++) {
    keyboard.keys[i].lastDown = keyboard.keys[i].down;
    keyboard.keys[i].down     = glfwGetKey(handle, i) == GLFW_PRESS;
  }
}

Mouse mouse;

bool isMouseButtonPressed(int button)
{
  return mouse.buttons[button].down && !mouse.buttons[button].lastDown;
}

bool isMouseButtonDown(int button)
{
  return mouse.buttons[button].down;
}

void Mouse_update(GLFWwindow *handle)
{
  // 32 is the first key
  for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++) {
    mouse.buttons[i].lastDown = mouse.buttons[i].down;
    mouse.buttons[i].down     = glfwGetMouseButton(handle, i) == GLFW_PRESS;
  }
}
