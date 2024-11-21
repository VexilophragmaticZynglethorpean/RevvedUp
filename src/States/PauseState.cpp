#include "States/PauseState.h"
#include "Core/SoundManager.h"
#include "Core/EventManager.h"
#include "Core/WindowManager.h"
#include "Core/StateManager.h"
#include "Core/TextureManager.h"
#include "Util/Path.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>

void PauseState::init() {
    auto& eventManager = EventManager::getInstance();
    auto& soundManager = SoundManager::getInstance();
    auto windowSize = WindowManager::getWindow().getSize();

    soundManager.getMusic().pause();

    overlay.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));

    font.loadFromFile(Util::getExecutablePath() / "assets/SuperchargeHalftone.otf");

    pauseText.setFont(font);
    pauseText.setString("PAUSED");
    pauseText.setCharacterSize(50);
    pauseText.setFillColor(sf::Color::White);

    auto localBounds = pauseText.getLocalBounds();
    pauseText.setOrigin(localBounds.width, localBounds.height);
    pauseText.setPosition(windowSize.x/2.0f, windowSize.y/2.0f);

    eventManager.addListener(StateID::Pause, sf::Event::KeyPressed, std::bind(&PauseState::handleEvents, this, std::placeholders::_1));

    eventManager.addListener(StateID::Pause, sf::Event::Closed, std::bind(&PauseState::handleEvents, this, std::placeholders::_1));
}

void PauseState::update(const sf::Time& deltaTime) {
}

void PauseState::render(sf::RenderTarget& target) {
    auto& snapshot = TextureManager::getInstance().getRenderTexture();

    target.draw(overlay);
    target.draw(pauseText);
}

void PauseState::exit() {
    SoundManager::getInstance().getMusic().play();
}

void PauseState::handleEvents(const sf::Event& event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            switch (event.key.code) {
                case sf::Keyboard::Escape:
                    std::clog << "unpause";
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
