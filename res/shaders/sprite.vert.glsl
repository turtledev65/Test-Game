#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTextureCoords;

out vec2 TextureCoords;

uniform mat4 uModel = mat4(1.0f);
uniform mat4 uView  = mat4(1.0f);
uniform mat4 uProj  = mat4(1.0f);

void main()
{
  gl_Position = uProj * uView * uModel * vec4(aPos, 1.0);
  TextureCoords = aTextureCoords;
}
