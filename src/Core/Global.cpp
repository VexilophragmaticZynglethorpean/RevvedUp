#include <Core/Global.h>

sf::RenderWindow& Global::getWindow() {
	static sf::RenderWindow window(sf::VideoMode(800, 600), "RevvedUp");
	return window;
}

sf::Texture& Global::getTexture() {
	static sf::Texture texture;
	return texture;
}

sf::Shader& Global::getShader() {
	static sf::Shader shader;
	return shader;
}
