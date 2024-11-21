#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "Components/PlayerCar.h"
#include "Components/Background.h"
#include "Core/IState.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include <SFML/Audio.hpp>

class PlayState : public State
{
  private:
    PlayerCar car;
    Background background;

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
