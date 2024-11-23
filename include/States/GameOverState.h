#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "Core/IState.h"
#include <SFML/Graphics.hpp>

class GameOverState : public State {
private:
    sf::RectangleShape overlay;
    sf::Text gameOverText;
    sf::Text timeText;
    sf::Text instructionsText;
    sf::Font font;
    sf::RenderTexture backgroundTexture;
    sf::Sprite backgroundSprite;
    float elapsedTime;

public:
    GameOverState();

    void init() override;
    void update(const sf::Time& deltaTime) override;
    void render(sf::RenderTarget& target) override;
    void handleEvents(const sf::Event& event) override;
    void exit() override;

    void setElapsedTime(float time) {
        elapsedTime = time;
    }
};

#endif // GAMEOVERSTATE_H

