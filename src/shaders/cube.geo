#version 330 core

layout(points) in;
layout(triangle_strip, max_vertices = 24) out;

in vec2 TexCoords[];
out vec2 FragTexCoords;

uniform mat4 ModelViewProjection;

void EmitFace(vec4 v1, vec4 v2, vec4 v3, vec4 v4)
{
    gl_Position = ModelViewProjection * v1;
    EmitVertex();
    gl_Position = ModelViewProjection * v2;
    EmitVertex();
    gl_Position = ModelViewProjection * v3;
    EmitVertex();
    gl_Position = ModelViewProjection * v4;
    EmitVertex();
    EndPrimitive();
}

void main()
{
    FragTexCoords = TexCoords[0];

    vec4 basePosition = gl_in[0].gl_Position;

    // Define the vertices for the cube faces
    vec4 vertices[8];
    vertices[0] = basePosition + vec4( 0.1,  0.1,  0.1, 0.0); // NEU
    vertices[1] = basePosition + vec4( 0.1,  0.1, -0.1, 0.0); // NWU
    vertices[2] = basePosition + vec4( 0.1, -0.1,  0.1, 0.0); // NED
    vertices[3] = basePosition + vec4( 0.1, -0.1, -0.1, 0.0); // NWD
    vertices[4] = basePosition + vec4(-0.1,  0.1,  0.1, 0.0); // SEU
    vertices[5] = basePosition + vec4(-0.1,  0.1, -0.1, 0.0); // SWU
    vertices[6] = basePosition + vec4(-0.1, -0.1,  0.1, 0.0); // SED
    vertices[7] = basePosition + vec4(-0.1, -0.1, -0.1, 0.0); // SWD

    // Emit the vertices for each face of the cube
    // Front face
    EmitFace(vertices[0], vertices[1], vertices[3], vertices[2]);
    // Back face
    EmitFace(vertices[4], vertices[6], vertices[7], vertices[5]);
    // Left face
    EmitFace(vertices[5], vertices[7], vertices[1], vertices[0]);
    // Right face
    EmitFace(vertices[2], vertices[3], vertices[5], vertices[4]);
    // Top face
    EmitFace(vertices[0], vertices[2], vertices[4], vertices[6]);
    // Bottom face
    EmitFace(vertices[1], vertices[3], vertices[7], vertices[5]);

    EndPrimitive();
}


