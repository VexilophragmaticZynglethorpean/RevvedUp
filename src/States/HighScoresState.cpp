#include "Util/Path.h"
#include "Core/StateManager.h"
#include "Core/EventManager.h"
#include "Core/WindowManager.h"
#include "Core/TextureManager.h"
#include <fstream>

#include "States/HighScoresState.h"

HighScoresState::HighScoresState()
: State(StateID::HighScores)
{
}

void HighScoresState::init() {
    auto& eventManager = EventManager::getInstance();
    auto windowSize = WindowManager::getWindow().getSize();

    auto& textureManager = TextureManager::getInstance();
    background.setTexture(textureManager.getTexture(TextureID::MENU_BACKGROUND));
    background.setScale(
        static_cast<float>(windowSize.x) / background.getTexture()->getSize().x,
        static_cast<float>(windowSize.y) / background.getTexture()->getSize().y
    );

    overlay.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    overlay.setFillColor(sf::Color(0, 0, 0, 230));

    font.loadFromFile(Util::getExecutablePath() / "assets/Sans.ttf");
    highScoresText.setFont(font);
    highScoresText.setCharacterSize(30);
    highScoresText.setFillColor(sf::Color::White);
    highScoresText.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
    highScoresText.setOrigin(highScoresText.getLocalBounds().width / 2, highScoresText.getLocalBounds().height / 2);

    loadHighScores();

    eventManager.addListener(StateID::HighScores, sf::Event::KeyPressed, std::bind(&HighScoresState::handleEvents, this, std::placeholders::_1));
    eventManager.addListener(StateID::HighScores, sf::Event::Closed, std::bind(&HighScoresState::handleEvents, this, std::placeholders::_1));
}

void HighScoresState::update(const sf::Time& deltaTime) {
}

void HighScoresState::render(sf::RenderTarget& target) {
    target.draw(background);
    target.draw(overlay);
    target.draw(highScoresText);
}

void HighScoresState::exit() {
    auto& eventManager = EventManager::getInstance();
    eventManager.removeAllListeners(StateID::HighScores, sf::Event::KeyPressed);
    eventManager.removeAllListeners(StateID::HighScores, sf::Event::Closed);
}

void HighScoresState::handleEvents(const sf::Event& event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape) {
                StateManager::getInstance().popState();
            }
            break;
        case sf::Event::Closed:
            WindowManager::getWindow().close();
            break;
        default:
            break;
    }
}

void HighScoresState::loadHighScores() {
    std::ifstream file("highscores.txt");
    std::string line;
    std::string scores;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            scores += line + "\n";
        }
        file.close();
    } else {
        scores = "No high scores available.";
    }

    highScoresText.setString(scores);
}
