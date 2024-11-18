#version 330 core

in vec2 FragTexCoords;
uniform sampler2D texture;

out vec4 FragColor;

void main()
{
   FragColor = texture2D(texture, FragTexCoords);
}
