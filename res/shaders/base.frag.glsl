#version 330 core

in vec2 TextureCoords;
out vec4 FragColor;

uniform sampler2D uContainerTexture;

void main()
{
  FragColor = texture(uContainerTexture, TextureCoords);
}
