#include "wall.h"
#include "gfx/texture.h"
#include "util/array.h"

#include <cglm/cglm.h>
#include <cglm/mat4.h>

void Wall_init(Wall *self, Tiles *tiles)
{
  float positions[] = {
      -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,
      1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,
      1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
      -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f,
      1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,
      1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f,
      1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,
      1.0f,  1.0f,  -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f,
      1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f,
      -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f,
  };
  float textureCoords[] = {
      0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
      1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  Geometry geometry;
  Geometry_init(&geometry);
  Geometry_setPositions(&geometry, positions, LENGTH(positions));
  Geometry_setTextureCoords(&geometry, textureCoords, LENGTH(textureCoords));

  size_t count = 0;
  for (int i = 0; i < tiles->length; i++) {
    Tile tile = tiles->data[i];
    if (tile.type != TILE_WALL_VERTICAL && tile.type != TILE_WALL_HORIZONTAL) {
      continue;
    }
    count++;
  }

  InstancedMesh_init(&self->mesh, &geometry, (vec3){0.6, 0.14f, 0.14f}, count);
  Texture texture;
  glActiveTexture(GL_TEXTURE0);
  Texture_init(&texture, "res/textures/Wall.png");
  InstancedMesh_setTexture(&self->mesh, &texture);

  size_t idx = 0;
  for (size_t i = 0; i < tiles->length; i++) {
    Tile tile = tiles->data[i];
    if (tile.type != TILE_WALL_VERTICAL && tile.type != TILE_WALL_HORIZONTAL) {
      continue;
    }
    mat4 model = GLM_MAT4_IDENTITY_INIT;
    glm_translate(model, (vec3){tile.x, -1.0f, tile.z});
    InstancedMesh_setMatrixAt(&self->mesh, idx++, model);
  }

  Geometry_free(&geometry);
}

void Wall_draw(Wall *self, Camera *camera)
{
  InstancedMesh_draw(&self->mesh, camera);
}
