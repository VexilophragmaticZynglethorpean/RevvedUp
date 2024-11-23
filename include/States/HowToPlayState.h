#ifndef HOWTOPLAYSTATE_H
#define HOWTOPLAYSTATE_H

#include "Core/IState.h"
#include "Core/EventManager.h"
#include "Core/WindowManager.h"
#include "Core/TextureManager.h"
#include <SFML/Graphics.hpp>
#include <functional>

class HowToPlayState : public State {
public:
    HowToPlayState();
    void init() override;
    void update(const sf::Time& deltaTime) override;
    void render(sf::RenderTarget& target) override;
    void exit() override;

private:
    void handleEvents(const sf::Event& event) override;
    sf::Font font;
    sf::Text instructionsText;
};

#endif // HOWTOPLAYSTATE_H