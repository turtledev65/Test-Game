#version 330 core

in vec3 Color;
out vec4 FragColor;

#ifdef TEXTURE
in vec2 TextureCoords;
uniform sampler2D texture1;
#endif

void main()
{
#ifdef TEXTURE
  FragColor = texture(texture1, TextureCoords);
#else
  FragColor = vec4(Color, 1.0f);
#endif
}
