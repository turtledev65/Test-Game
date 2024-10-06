#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 uModel = mat4(1.0f);
uniform mat4 uView = mat4(1.0f);
uniform mat4 uProj = mat4(1.0f);

uniform vec3 uColor = vec3(0.0f);
out vec3 Color;

void main()
{
  gl_Position = uProj * uView * uModel * vec4(aPos, 1.0f);
  Color = uColor;
}
