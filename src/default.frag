#version 460 core

in vec3 fragColor;
out vec4 outputColor;

void main() {
    outputColor = vec4(fragColor, 1.0);
}
