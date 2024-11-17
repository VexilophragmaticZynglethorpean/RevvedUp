#version 330 core

in vec2 TexCoords;
uniform sampler2D texture;

out vec4 FragColor;

void main()
{
    FragColor = texture2D(texture, TexCoords);
}
