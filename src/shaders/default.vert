#version 330 core

layout(location = 0) in vec2 position; 
layout(location = 1) in uvec4 color;
layout(location = 1) in vec2 texCoords;

out vec2 TexCoords;

uniform mat4 ModelViewProjection;

void main()
{
    float sign = (color.g != 0.0) ? -1.0 : 1.0;
    gl_Position = ModelViewProjection * vec4(position.xy, sign * color.r, 1.0);
}
