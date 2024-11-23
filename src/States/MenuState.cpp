#include "States/MenuState.h"
#include "Core/FontManager.h"
#include "Core/TextureManager.h"
#include "States/PlayState.h"
#include "States/HowToPlayState.h"
#include "States/SettingsState.h"
#include "States/HighScoresState.h"
#include "Core/EventManager.h"
#include "Core/StateManager.h"
#include "Core/WindowManager.h"
#include "Util/Path.h"
#include "Util/Path.h"
#include <SFML/Graphics.hpp>
#include <functional>

MenuState::MenuState()
: State(StateID::Menu), defaultColor(sf::Color::White), hoverColor(sf::Color::Yellow), selectedButtonIndex(0)
{
}

void MenuState::init() {
    auto& eventManager = EventManager::getInstance();
    auto windowSize = WindowManager::getWindow().getSize();

    overlay.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    overlay.setFillColor(sf::Color(0, 0, 0, 230));
    
    auto& textureManager = TextureManager::getInstance();
    textureManager.loadTexture(TextureID::MENU_BACKGROUND, Util::getExecutablePath() / "assets/menu_background.jpg");
    background.setTexture(textureManager.getTexture(TextureID::MENU_BACKGROUND));
    background.setScale(
        static_cast<float>(windowSize.x) / background.getTexture()->getSize().x,
        static_cast<float>(windowSize.y) / background.getTexture()->getSize().y
    );

    FontManager::getInstance().loadFont( FontID::TITLE, Util::getExecutablePath() / "assets/PreschoolBits.ttf");
    FontManager::getInstance().loadFont( FontID::TEXT, Util::getExecutablePath() / "assets/Sans.ttf");
    FontManager::getInstance().loadFont( FontID::FANCY, Util::getExecutablePath() / "assets/SuperchargeHalftone.otf");

    auto& font = FontManager::getInstance().getFont(FontID::TITLE);
    title.setFont(font);
    title.setString("Race");
    title.setCharacterSize(120);
    title.setFillColor(defaultColor);
    title.setPosition(windowSize.x / 2.0f, windowSize.y / 4.0f);
    title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);

    std::vector<std::string> buttonLabels = {"Play", "How to Play", "High Scores", "Settings"};
    for (size_t i = 0; i < buttonLabels.size(); ++i) {
        sf::Text buttonText;
        buttonText.setFont(font);
        buttonText.setString(buttonLabels[i]);
        buttonText.setCharacterSize(40);
        buttonText.setFillColor(defaultColor);
        buttonText.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f + i * 65);
        buttonText.setOrigin(buttonText.getLocalBounds().width / 2, buttonText.getLocalBounds().height / 2);
        buttons.push_back(buttonText);

        sf::RectangleShape buttonBackground;
        buttonBackground.setSize(sf::Vector2f(400, 60));
        buttonBackground.setFillColor(sf::Color(0, 0, 0));
        buttonBackground.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f + i * 66 + 5 );
        buttonBackground.setOrigin(buttonBackground.getSize().x / 2, buttonBackground.getSize().y / 2);
        buttonBackgrounds.push_back(buttonBackground);
    }

    eventManager.addListener(
      StateID::Menu, sf::Event::KeyPressed, std::bind(&WindowManager::toggleFullScreen, std::placeholders::_1));
    eventManager.addListener(StateID::Menu, sf::Event::KeyPressed, std::bind(&MenuState::handleEvents, this, std::placeholders::_1));
    eventManager.addListener(StateID::Menu, sf::Event::MouseButtonPressed, std::bind(&MenuState::handleEvents, this, std::placeholders::_1));
    eventManager.addListener(StateID::Menu, sf::Event::Closed, std::bind(&MenuState::handleEvents, this, std::placeholders::_1));
}

void MenuState::update(const sf::Time& deltaTime) {
    auto mousePos = sf::Mouse::getPosition(WindowManager::getWindow());
    updateButtonStates(static_cast<sf::Vector2f>(mousePos));
}

void MenuState::render(sf::RenderTarget& target) {
    target.draw(background);
    target.draw(overlay);
    target.draw(title);
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
    eventManager.removeAllListeners(StateID::Menu, sf::Event::MouseButtonPressed);
    eventManager.removeAllListeners(StateID::Menu, sf::Event::Closed);
}

void MenuState::handleEvents(const sf::Event& event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape) {
                WindowManager::getWindow().close();
            } else if (event.key.code == sf::Keyboard::Up) {
                // Move selection up
                selectedButtonIndex = (selectedButtonIndex > 0) ? selectedButtonIndex - 1 : buttons.size() - 1;
            } else if (event.key.code == sf::Keyboard::Down) {
                // Move selection down
                selectedButtonIndex = (selectedButtonIndex + 1) % buttons.size();
            } else if (event.key.code == sf::Keyboard::Enter) {
                // Select the currently highlighted button
                handleButtonPress(selectedButtonIndex);
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
        // Check if the mouse is over the button or if it's the selected button
        if (buttonBackgrounds[i].getGlobalBounds().contains(mousePos)) {
            buttons[i].setFillColor(hoverColor);
            selectedButtonIndex = i; // Update selected index based on mouse hover
        } else if (i == selectedButtonIndex) {
            buttons[i].setFillColor(hoverColor); // Highlight the selected button
        } else {
            buttons[i].setFillColor(defaultColor); // Default color for unselected buttons
        }
    }
}
