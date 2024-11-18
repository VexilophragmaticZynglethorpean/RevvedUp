#ifndef CUBE_H
#define CUBE_H

#include <SFML/Graphics.hpp>
#include <3DExtensions/Transformable3D.h>
#include <3DExtensions/VertexBuffer3D.h>

class Cube : public sf::Drawable, public Transformable3D {
private:
	std::vector<Vertex3D> verticesArray;
        VertexBuffer3D buffer;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Cube();

	void init(bool viewedFromOutside = true);
};

#endif // CUBE_H
