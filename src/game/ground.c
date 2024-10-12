#include "ground.h"

void Ground_init(Ground *self, Tiles *tiles)
{
  float vertices[] = {
      -1.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.0f,
      1.0f,  1.0f, 0.0f, 1.0f,  -1.0f, 0.0f,
  };
  unsigned int indices[] = {
      0, 1, 2, 1, 2, 3,
  };

  mat4   modelMatrices[tiles->length];
  size_t count = 0;
  for (int i = 0; i < tiles->length; i++) {
    if (tiles->data[i].type != TILE_GROUND)
      continue;

    mat4 model = GLM_MAT4_IDENTITY_INIT;
    glm_translate(model, (vec3){tiles->data[i].x, -2.0f, tiles->data[i].z});
    glm_rotate(model, glm_rad(90.0f), (vec3){1.0f, 0.0f, 0.0f});
    glm_mat4_copy(model, modelMatrices[count++]);
  }

  InstancedMesh_init(&self->mesh, count, modelMatrices, vertices,
                     sizeof(vertices) / sizeof(vertices[0]), indices,
                     sizeof(indices) / sizeof(indices[0]),
                     (vec3){0.47f, 0.24f, 0.24f});
}

void Ground_draw(Ground *self, Camera *camera)
{
  InstancedMesh_draw(&self->mesh, camera);
}
