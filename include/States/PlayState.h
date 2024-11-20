#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "Components/Car.h"
#include "Components/Background.h"
#include "Core/State.h"
#include <SFML/Audio.hpp>

class PlayState : public State
{
  private:
    Car car;
    Background background;
    std::vector<sf::SoundBuffer> soundBuffers;
    sf::Sound sound;

  public:
    PlayState();

    void update(const sf::Time& deltaTime) override;
    void render() override;

    void init() override;
    void exit() override;
    void resize(const sf::Event& event);
};

#endif // PLAY_STATE_H
