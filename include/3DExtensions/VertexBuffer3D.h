#ifndef VERTEX_BUFFER_3D_H
#define VERTEX_BUFFER_3D_H

#include <SFML/Graphics.hpp>
#include <3DExtensions/Vertex3D.h>
#include <glad/gl.h>

class VertexBuffer3D {
public:
	enum Usage { Stream, Dynamic, Static };

	VertexBuffer3D(sf::PrimitiveType type, Usage usage = Usage::Stream);
	~VertexBuffer3D();

	void create();
	void update(const std::vector<Vertex3D>& vertex);
	void bind() const;

	sf::PrimitiveType getPrimitiveType() const;
	Usage getUsage() const;

private:
	sf::PrimitiveType type;
	Usage usage;
	GLuint vbo;
	GLuint vao;
};

#endif // VERTEX_BUFFER_3D_H

