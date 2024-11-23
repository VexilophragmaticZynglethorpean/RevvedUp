#include "States/GameOverState.h"
#include "Core/SoundManager.h"
#include "Core/EventManager.h"
#include "Core/WindowManager.h"
#include "Core/StateManager.h"
#include "Core/TextureManager.h"
#include "Core/FontManager.h"
#include <functional>

GameOverState::GameOverState()
: State(StateID::GameOver), elapsedTime(0.0f) {
}

void GameOverState::init() {
    auto& eventManager = EventManager::getInstance();
    auto& soundManager = SoundManager::getInstance();
    auto windowSize = WindowManager::getWindow().getSize();

    soundManager.getMusic().stop();

    overlay.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    overlay.setFillColor(sf::Color(0, 0, 0, 230));

    auto& font = FontManager::getInstance().getFont(FontID::FANCY);
    auto& textFont = FontManager::getInstance().getFont(FontID::TEXT);

    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::White);
    auto localBounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(localBounds.width / 2.0f, localBounds.height / 2.0f);
    gameOverText.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f - 20);

    timeText.setFont(textFont);
    timeText.setCharacterSize(30);
    timeText.setFillColor(sf::Color::White);
    auto timeLocalBounds = timeText.getLocalBounds();
    timeText.setPosition(windowSize.x / 2.0f - localBounds.width / 2.0f, windowSize.y / 2.0f + localBounds.height / 2.0f + timeText.getCharacterSize());
    
    instructionsText.setFont(textFont);
    instructionsText.setString("Press Esc to return to main menu");
    instructionsText.setCharacterSize(15);
    instructionsText.setFillColor(sf::Color::White);
    instructionsText.setPosition(0.0f, windowSize.y - instructionsText.getCharacterSize() * 1);

    eventManager.addListener(StateID::GameOver, sf::Event::KeyPressed, std::bind(&GameOverState::handleEvents, this, std::placeholders::_1));
    eventManager.addListener(StateID::GameOver, sf::Event::Closed, std::bind(&GameOverState::handleEvents, this, std::placeholders::_1));
}

void GameOverState::update(const sf::Time& deltaTime) {
    timeText.setString("Time: " + std::to_string(elapsedTime) + " seconds");
}

void GameOverState::render(sf::RenderTarget& target) {
    auto& snapshot = TextureManager::getInstance().getRenderTexture();
    sf::Sprite snapshotSprite(snapshot.getTexture());
    target.draw(snapshotSprite);
    target.draw(overlay);
    target.draw(gameOverText);
    target.draw(timeText);
    target.draw(instructionsText);
}

void GameOverState::exit() {
    auto& eventManager = EventManager::getInstance();
    eventManager.removeAllListeners(StateID::GameOver, sf::Event::KeyPressed);
    eventManager.removeAllListeners(StateID::GameOver, sf::Event::Closed);
}

void GameOverState::handleEvents(const sf::Event& event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            switch (event.key.code) {
                case sf::Keyboard::Escape:
                    StateManager::getInstance().popState();
                    StateManager::getInstance().popState();
                    break;
                default:
                    break;
            }
            break;
        case sf::Event::Closed:
            WindowManager::getWindow().close();
            break;
        default:
            break;
    }
}
