#include "States/MenuState.h"
#include "States/PlayState.h"
#include "States/HowToPlayState.h"
#include "States/SettingsState.h"
#include "States/HighScoresState.h"

#include "Core/EventManager.h"
#include "Core/StateManager.h"
#include "Core/WindowManager.h"
#include "Util/Path.h"
#include <SFML/Graphics.hpp>
#include <functional>

MenuState::MenuState()
: State(StateID::Menu), defaultColor(sf::Color::White), hoverColor(sf::Color::Yellow)
{
}

void MenuState::init() {
    auto& eventManager = EventManager::getInstance();
    auto windowSize = WindowManager::getWindow().getSize();

    overlay.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    overlay.setFillColor(sf::Color(0, 0, 0, 230));

    font.loadFromFile(Util::getExecutablePath() / "assets/SuperchargeHalftone.otf");

    // Create buttons
    std::vector<std::string> buttonLabels = {"Play", "How to Play", "High Scores", "Settings"};
    for (size_t i = 0; i < buttonLabels.size(); ++i) {
        sf::Text buttonText;
        buttonText.setFont(font);
        buttonText.setString(buttonLabels[i]);
        buttonText.setCharacterSize(40);
        buttonText.setFillColor(defaultColor);
        buttonText.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f + i * 60);
        buttonText.setOrigin(buttonText.getLocalBounds().width / 2, buttonText.getLocalBounds().height / 2);
        buttons.push_back(buttonText);

        sf::RectangleShape buttonBackground;
        buttonBackground.setSize(sf::Vector2f(300, 50));
        buttonBackground.setFillColor(sf::Color(100, 100, 100));
        buttonBackground.setPosition(windowSize.x / 2.0f - 150, windowSize.y / 2.0f + i * 60 - 25);
        buttonBackground.setOrigin(buttonBackground.getSize().x / 2, buttonBackground.getSize().y / 2);
        buttonBackgrounds.push_back(buttonBackground);
    }

    eventManager.addListener(StateID::Menu, sf::Event::KeyPressed, std::bind(&MenuState::handleEvents, this, std::placeholders::_1));
    eventManager.addListener(StateID::Menu, sf::Event::Closed, std::bind(&MenuState::handleEvents, this, std::placeholders::_1));
}

void MenuState::update(const sf::Time& deltaTime) {
    // Update button states based on mouse position
    auto mousePos = sf::Mouse::getPosition(WindowManager::getWindow());
    updateButtonStates(static_cast<sf::Vector2f>(mousePos));
}

void MenuState::render(sf::RenderTarget& target) {
    target.draw(overlay);
    for (const auto& buttonBackground : buttonBackgrounds) {
        target.draw(buttonBackground);
    }
    for (const auto& button : buttons) {
        target.draw(button);
    }
}

void MenuState::exit() {
    auto& eventManager = EventManager::getInstance();
    eventManager.removeAllListeners(StateID::Menu, sf::Event::KeyPressed);
    eventManager.removeAllListeners(StateID::Menu, sf::Event::Closed);
}

void MenuState::handleEvents(const sf::Event& event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape) {
                WindowManager::getWindow().close();
            }
            break;
        case sf::Event::Closed:
            WindowManager::getWindow().close();
            break;
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left) {
                auto mousePos = sf::Mouse::getPosition(WindowManager::getWindow());
                for (size_t i = 0; i < buttonBackgrounds.size(); ++i) {
                    if (buttonBackgrounds[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        handleButtonPress(i);
                    }
                }
            }
            break;
        default:
            break;
    }
}

void MenuState::handleButtonPress(int buttonIndex) {
    switch (buttonIndex) {
        case 0: // Play
            StateManager::getInstance().pushState(std::make_unique<PlayState>());
            break;
        case 1: // How to Play
            StateManager::getInstance().pushState(std::make_unique<HowToPlayState>());
            break;
        case 2: // High Scores
            StateManager::getInstance().pushState(std::make_unique<HighScoresState>());
            break;
        case 3: // Settings
            StateManager::getInstance().pushState(std::make_unique<SettingsState>());
            break;
        default:
            break;
    }
}

void MenuState::updateButtonStates(const sf::Vector2f& mousePos) {
    for (size_t i = 0; i < buttonBackgrounds.size(); ++i) {
        if (buttonBackgrounds[i].getGlobalBounds().contains(mousePos)) {
            buttons[i].setFillColor(hoverColor);
        } else {
            buttons[i].setFillColor(defaultColor);
        }
    }
}
