#include "ground.h"
#include "gfx/geometry.h"
#include "util/array.h"

void Ground_init(Ground *self, Tiles *tiles)
{
  float positions[] = {
      -1.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.0f,
      1.0f,  1.0f, 0.0f, 1.0f,  -1.0f, 0.0f,
  };
  unsigned int indices[] = {
      0, 1, 2, 1, 2, 3,
  };

  Geometry geometry;
  Geometry_init(&geometry);
  Geometry_setPositions(&geometry, positions, LENGTH(positions));
  Geometry_setIndices(&geometry, indices, LENGTH(indices));

  size_t count = 0;
  for (int i = 0; i < tiles->length; i++) {
    if (tiles->data[i].type != TILE_GROUND)
      continue;
    count++;
  }
  InstancedMesh_init(&self->mesh, &geometry, (vec3){0.47f, 0.24f, 0.24f},
                     count);

  size_t idx = 0;
  for (size_t i = 0; i < tiles->length; i++) {
    Tile tile = tiles->data[i];
    if (tiles->data[i].type != TILE_GROUND)
      continue;

    mat4 model = GLM_MAT4_IDENTITY_INIT;
    glm_translate(model, (vec3){tile.x, -2.0f, tile.z});
    glm_rotate(model, glm_rad(90.0f), (vec3){1.0f, 0.0f, 0.0f});
    InstancedMesh_setMatrixAt(&self->mesh, idx++, model);
  }
  InstancedMesh_sendModelMatrices(&self->mesh);
}

void Ground_draw(Ground *self, Camera *camera)
{
  InstancedMesh_draw(&self->mesh, camera);
}
