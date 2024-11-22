#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "Components/PlayerCar.h"
#include "Components/Jeep.h"
#include "Components/Background.h"
#include "Core/IState.h"
#include <SFML/Audio.hpp>
#include <deque>

class PlayState : public State
{
  private:
    PlayerCar car;
    Background background;
    std::deque<Jeep> traffic;

  public:
    PlayState();

    void init() override;
    void update(const sf::Time& deltaTime) override;
    void render(sf::RenderTarget& target) override;
    void handleEvents(const sf::Event& event) override;
    void exit() override;

    void snapshot(sf::RenderTexture& renderTexture);
};

#endif // PLAY_STATE_H
