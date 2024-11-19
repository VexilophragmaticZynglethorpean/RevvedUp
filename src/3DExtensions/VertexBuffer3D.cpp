#include "3DExtensions/VertexBuffer3D.h"

GLenum
usageToGlEnum(VertexBuffer3D::Usage usage)
{
    switch (usage) {
        case VertexBuffer3D::Usage::Static:
            return GL_STATIC_DRAW;
        case VertexBuffer3D::Usage::Dynamic:
            return GL_DYNAMIC_DRAW;
        default:
            return GL_STREAM_DRAW;
    }
}

VertexBuffer3D::VertexBuffer3D(sf::PrimitiveType type, Usage usage)
  : type(type)
  , usage(usage)
  , ebo(0)
  , vbo(0)
  , vao(0)
{
}

VertexBuffer3D::~VertexBuffer3D()
{
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}

void
VertexBuffer3D::update(const std::vector<Vertex3D>& vertices,
                       const std::vector<GLuint>& indices)
{
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ARRAY_BUFFER,
                 vertices.size() * sizeof(Vertex3D),
                 vertices.data(),
                 usageToGlEnum(usage));

    if (vertices.size() != 0) {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     indices.size() * sizeof(GLuint),
                     indices.data(),
                     usageToGlEnum(usage));
    }

    glVertexAttribPointer(0,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(GLfloat),
                          (void*)offsetof(Vertex3D, position));

    glVertexAttribPointer(1,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(GLfloat),
                          (void*)offsetof(Vertex3D, texCoords));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}

void
VertexBuffer3D::create()
{
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &vao);
}

void
VertexBuffer3D::bind() const
{
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

sf::PrimitiveType
VertexBuffer3D::getPrimitiveType() const
{
    return type;
}

VertexBuffer3D::Usage
VertexBuffer3D::getUsage() const
{
    return usage;
}
