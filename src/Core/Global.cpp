#include <Core/Global.h>

sf::RenderWindow& Global::getWindow() {
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	settings.attributeFlags = sf::ContextSettings::Attribute::Debug;

	static sf::RenderWindow window(sf::VideoMode(800, 600), "RevvedUp", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close, settings);

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

sf::Clock& Global::getClock() {
	static sf::Clock clock;
	return clock;
}
