#ifndef VERTEX_3D_H
#define VERTEX_3D_H

#include <SFML/Graphics.hpp>

class Vertex3D {
public:
	Vertex3D()
		: position(0, 0, 0), texCoords(0, 0) {}

	Vertex3D(const sf::Vector3f& thePosition)
		: position(thePosition), texCoords(0, 0) {}

	Vertex3D(const sf::Vector3f& thePosition, const sf::Vector2f& theTexCoords)
		: position(thePosition), texCoords(theTexCoords) {}

	sf::Vector3f position;
	sf::Vector2f texCoords;
};

#endif // VERTEX_3D_H
