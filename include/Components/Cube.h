#ifndef CUBE_H
#define CUBE_H

#include <SFML/Graphics.hpp>
#include <Components/Transformable3D.h>

class Cube : public sf::Drawable, public Transformable3D {
private:
	std::vector<sf::Vertex> verticesArray;
        sf::VertexBuffer buffer;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Cube();

	void init(bool viewedFromOutside = true);
};

#endif // CUBE_H
