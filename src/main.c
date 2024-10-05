#include <stdlib.h>
#include <stdio.h>

#include "core/app.h"
#include "core/input.h"

static App app;

static void update()
{
  if (isKeyDown(GLFW_KEY_ESCAPE)) {
    App_quit(&app);
  }
}

int main()
{
  App_init(&app, NULL, update, NULL, NULL);
  App_update(&app);
}
