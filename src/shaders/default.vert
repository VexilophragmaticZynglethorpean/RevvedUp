uniform mat4 ModelViewProjection;

void main()
{
    float sign = (gl_Color.g != 0.0) ? -1.0 : 1.0;
    gl_Position = ModelViewProjection * vec4(gl_Vertex.xy, sign * gl_Color.r, 1.0);
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
}
