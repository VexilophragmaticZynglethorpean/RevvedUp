#ifndef HIGHSCORESSTATE_H
#define HIGHSCORESSTATE_H

#include "Core/IState.h"
#include "Core/EventManager.h"
#include "Core/WindowManager.h"
#include "Core/TextureManager.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>

class HighScoresState : public State {
public:
    HighScoresState();
    void init() override;
    void update(const sf::Time& deltaTime) override;
    void render(sf::RenderTarget& target) override;
    void exit() override;

private:
    void handleEvents(const sf::Event& event) override;
    void loadHighScores();
    
    sf::Font font;
    sf::Text highScoresText;
    std::vector<std::string> highScores;
};

#endif // HIGHSCORESSTATE_H
