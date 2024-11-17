#ifndef CUBE_H
#define CUBE_H

#include <SFML/Graphics.hpp>
#include <Components/Transformable3D.h>
#include <memory>

class Cube : public sf::Drawable, public Transformable3D {
private:
	sf::VertexArray verticesArray;
	std::shared_ptr<const sf::Texture> texture;

public:
	Cube();

	void init(
		std::shared_ptr <sf::RenderTarget> window,
		std::shared_ptr<const sf::Texture> textureAtlas,
		bool viewedFromOutside
	);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	
};

#endif // CUBE_H
