#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <Core/State.h>
#include <Components/Car.h>
#include <Components/Cube.h>
#include <Components/Camera.h>

#include <memory>

class PlayState : public State {
private:
	std::shared_ptr<sf::Texture> textureAtlas;
	sf::Shader shader;
	Car car;
	Cube cube;
	Camera camera;

public:
	PlayState();

	void update(std::shared_ptr <const sf::RenderWindow> window, const sf::Time& deltaTime) override;
	void render(std::shared_ptr <sf::RenderTarget> window) override;

	void init(std::shared_ptr <sf::RenderWindow> window) override;
	void exit() override;
};

#endif // PLAY_STATE_H
