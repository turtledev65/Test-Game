#include "wall.h"

#include <cglm/cglm.h>
#include <cglm/mat4.h>

void Wall_init(Wall *self, Tiles *tiles)
{
  float vertices[] = {
      // position
      -1.0f, -1.0f, -1.0f, //
      1.0f,  -1.0f, -1.0f, //
      1.0f,  1.0f,  -1.0f, //
      1.0f,  1.0f,  -1.0f, //
      -1.0f, 1.0f,  -1.0f, //
      -1.0f, -1.0f, -1.0f, //

      -1.0f, -1.0f, 1.0f, //
      1.0f,  -1.0f, 1.0f, //
      1.0f,  1.0f,  1.0f, //
      1.0f,  1.0f,  1.0f, //
      -1.0f, 1.0f,  1.0f, //
      -1.0f, -1.0f, 1.0f, //

      -1.0f, 1.0f,  1.0f,  //
      -1.0f, 1.0f,  -1.0f, //
      -1.0f, -1.0f, -1.0f, //
      -1.0f, -1.0f, -1.0f, //
      -1.0f, -1.0f, 1.0f,  //
      -1.0f, 1.0f,  1.0f,  //

      1.0f,  1.0f,  1.0f,  //
      1.0f,  1.0f,  -1.0f, //
      1.0f,  -1.0f, -1.0f, //
      1.0f,  -1.0f, -1.0f, //
      1.0f,  -1.0f, 1.0f,  //
      1.0f,  1.0f,  1.0f,  //

      -1.0f, -1.0f, -1.0f, //
      1.0f,  -1.0f, -1.0f, //
      1.0f,  -1.0f, 1.0f,  //
      1.0f,  -1.0f, 1.0f,  //
      -1.0f, -1.0f, 1.0f,  //
      -1.0f, -1.0f, -1.0f, //

      -1.0f, 1.0f,  -1.0f, //
      1.0f,  1.0f,  -1.0f, //
      1.0f,  1.0f,  1.0f,  //
      1.0f,  1.0f,  1.0f,  //
      -1.0f, 1.0f,  1.0f,  //
      -1.0f, 1.0f,  -1.0f, //
  };

  mat4   modelMatrices[tiles->length];
  size_t count = 0;
  for (int i = 0; i < tiles->length; i++) {
    Tile tile = tiles->data[i];
    if (tile.type != TILE_WALL_VERTICAL && tile.type != TILE_WALL_HORIZONTAL) {
      continue;
    }

    mat4 model = GLM_MAT4_IDENTITY_INIT;
    glm_translate(model, (vec3){tile.x, -1.0f, tile.z});
    glm_mat4_copy(model, modelMatrices[count++]);
  }

  InstancedMesh_init(&self->mesh, count, modelMatrices, vertices,
                     sizeof(vertices) / sizeof(vertices[0]), NULL, 0,
                     (vec3){0.6, 0.14f, 0.14f});
}

void Wall_draw(Wall *self, Camera *camera)
{
  InstancedMesh_draw(&self->mesh, camera);
}
