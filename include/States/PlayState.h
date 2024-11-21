#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "Components/Car.h"
#include "Components/Background.h"
#include "Core/State.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include <SFML/Audio.hpp>

class PlayState : public State
{
  private:
    Car car;
    Background background;

  public:
    PlayState();

    void init() override;
    void update(const sf::Time& deltaTime) override;
    void render(sf::RenderTarget& target) override;
    void handleEvents(const sf::Event& event) override;
    void exit() override;
};

#endif // PLAY_STATE_H
