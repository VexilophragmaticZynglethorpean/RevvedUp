#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <Core/State.h>
#include <Components/Car.h>
#include <Components/Cube.h>
#include <Components/Camera.h>

#include <chrono>

class PlayState : public State {
private:
	Car car;
	Cube cube;
	Camera camera;
	std::chrono::time_point<std::chrono::high_resolution_clock> t_start;

public:
	PlayState();

	void update(const sf::Time& deltaTime) override;
	void render() override;

	void init() override;
	void exit() override;
	void resize();
};

#endif // PLAY_STATE_H
