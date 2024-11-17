#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>
#include <memory>

namespace Graphics {
	sf::Vertex Vertex3D(
		const std::shared_ptr<const sf::RenderTarget> target,
		const sf::Vector3f positionNDC,
		const std::shared_ptr<const sf::Texture> texTarget,
		const sf::Vector2f texNDC
	);
};

#endif // GRAPHICS_H
