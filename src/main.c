#include <stdlib.h>
#include <stdio.h>

#include "game/camera.h"

#include "gfx/gbuffer.h"
#include "gfx/shader.h"
#include "gfx/texture.h"
#include "gfx/vao.h"

#include "core/app.h"
#include "core/input.h"

static App app;

static Vao     vao;
static GBuffer vbo;
static GBuffer ibo;
static Shader  shader;
static Texture containerTexture;

static Camera camera;

static void init()
{
  float vertices[] = {
      // position         // texture coords
      -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, // top left
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
      0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // top right
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
  };
  GBuffer_init(&vbo, GL_ARRAY_BUFFER, false);
  GBuffer_data(&vbo, sizeof(vertices), vertices);

  unsigned int indices[] = {
      0, 1, 2, // First Triagnle
      1, 2, 3  // Second Triangle
  };
  GBuffer_init(&ibo, GL_ELEMENT_ARRAY_BUFFER, false);
  GBuffer_data(&ibo, sizeof(indices), indices);

  Vao_init(&vao);
  Vao_attribPointer(&vao, &vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), 0);
  Vao_attribPointer(&vao, &vbo, 1, 2, GL_FLOAT, 5 * sizeof(float),
                    3 * sizeof(float));

  Shader_init(&shader, "res/shaders/base.vert.glsl",
              "res/shaders/base.frag.glsl");

  glActiveTexture(GL_TEXTURE0);
  Texture_init(&containerTexture, GL_RGB, "res/textures/container.jpg");

  Camera_init(&camera, 9.0f);
}

static void draw()
{
  Shader_use(&shader);

  Shader_setInt(&shader, "uContainerTexture", 0);

  mat4 view;
  Camera_getViewMatrix(&camera, view);
  Shader_setMat4(&shader, "uView", view);

  mat4 proj;
  Camera_getProjectionMatrix(&camera, &(vec2s){.x = 900, .y = 600}, proj);
  Shader_setMat4(&shader, "uProj", proj);

  glActiveTexture(GL_TEXTURE0);
  Texture_bind(&containerTexture);

  Vao_bind(&vao);
  GBuffer_bind(&vbo);
  GBuffer_bind(&ibo);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}

static void update()
{
  if (isKeyDown(GLFW_KEY_ESCAPE)) {
    App_quit(&app);
  }

  Camera_update(&camera);
}

int main()
{
  App_init(&app, init, update, draw, NULL);
  App_update(&app);
}
