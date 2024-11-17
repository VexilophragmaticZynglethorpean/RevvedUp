#include <Core/Graphics.h>

#include <algorithm>
#include <cmath>

void convertFromNDC(const sf::Vector2u& size, float& x, float& y) {
	y = -y;

	x += 1;
	y += 1;

	x /= 2;
	y /= 2;

	x *= size.x;
	y *= size.y;
}

uint8_t convertToSFUint8(float z) {
	z = std::abs(z) * 255;
	return static_cast<uint8_t>(std::clamp(z, 0.0f, 255.0f));
}

sf::Vertex Graphics::Vertex3D(
	const std::shared_ptr<const sf::RenderTarget> target,
	const sf::Vector3f positionNDC,
	const std::shared_ptr<const sf::Texture> texTarget,
	const sf::Vector2f texNDC
) {
	sf::Vertex vertex;

	vertex.position.x = positionNDC.x;
	vertex.position.y = positionNDC.y;
	vertex.color.r = convertToSFUint8(positionNDC.z);
	vertex.color.g = (positionNDC.z < 0) ? (1 << 0) : 0;

	vertex.texCoords.x = texNDC.x;
	vertex.texCoords.y = texNDC.y;

	convertFromNDC(target->getSize(), vertex.position.x, vertex.position.y);
	convertFromNDC(texTarget->getSize(), vertex.texCoords.x, vertex.texCoords.y);

	return vertex;
}

