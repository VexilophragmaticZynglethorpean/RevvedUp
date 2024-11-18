#include <3DExtensions/VertexBuffer3D.h>

GLenum usageToGlEnum(VertexBuffer3D::Usage usage) {
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
	: type(type), usage(usage), vbo(0), vao(0) {
}

VertexBuffer3D::~VertexBuffer3D() {
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

void VertexBuffer3D::update(const std::vector<Vertex3D>& vertex) {
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex3D), vertex.data(), usageToGlEnum(usage));

	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, texCoords));

}

void VertexBuffer3D::create() {
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
}

void VertexBuffer3D::bind() const {
	glBindVertexArray(vao);
}

sf::PrimitiveType VertexBuffer3D::getPrimitiveType() const {
	return type;
}

VertexBuffer3D::Usage VertexBuffer3D::getUsage() const {
	return usage;
}

