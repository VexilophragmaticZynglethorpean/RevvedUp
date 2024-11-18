#version 330 core

layout(location = 0) in vec3 position; 
layout(location = 1) in vec2 texCoords;

out vec2 TexCoords;

uniform mat4 ModelViewProjection;

void main()
{
    gl_Position = ModelViewProjection * vec4(position.xy, 0.0, 1.0);
}
