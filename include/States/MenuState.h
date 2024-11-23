#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "Core/IState.h"
#include <vector>

class MenuState : public State {
public:
    MenuState();
    void init() override;
    void update(const sf::Time& deltaTime) override;
    void render(sf::RenderTarget& target) override;
    void exit() override;

private:
    void handleEvents(const sf::Event& event) override;
    void handleButtonPress(int buttonIndex);
    void updateButtonStates(const sf::Vector2f& mousePos);

    sf::RectangleShape overlay;
    sf::Font font;
    std::vector<sf::Text> buttons;
    std::vector<sf::RectangleShape> buttonBackgrounds;
    sf::Color defaultColor;
    sf::Color hoverColor;
};

#endif // MENUSTATE_H
