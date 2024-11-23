#include "States/MenuState.h"
#include "Core/FontManager.h"
#include "Core/SoundManager.h"
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
    auto& soundManager = SoundManager::getInstance();
    auto& fontManager = FontManager::getInstance();


    textureManager.loadTexture(TextureID::MENU_BACKGROUND, Util::getExecutablePath() / "assets/menu_background.jpg");
    background.setTexture(textureManager.getTexture(TextureID::MENU_BACKGROUND));
    background.setScale(
        static_cast<float>(windowSize.x) / background.getTexture()->getSize().x,
        static_cast<float>(windowSize.y) / background.getTexture()->getSize().y
    );

    soundManager.loadSound(SoundID::HOVER, Util::getExecutablePath() / "assets/hover.ogg");

    fontManager.loadFont( FontID::TITLE, Util::getExecutablePath() / "assets/PreschoolBits.ttf");
    fontManager.loadFont( FontID::TEXT, Util::getExecutablePath() / "assets/Sans.ttf");
    fontManager.loadFont( FontID::FANCY, Util::getExecutablePath() / "assets/SuperchargeHalftone.otf");

    auto& font = fontManager.getFont(FontID::TITLE);
    title.setFont(font);
    title.setString("Race");
    title.setCharacterSize(120);
    title.setFillColor(defaultColor);
    title.setPosition(windowSize.x / 2.0f, windowSize.y / 4.0f);
    title.setOrigin(title.getLocalBounds().width / 2.0f, title.getLocalBounds().height / 2.0f);

    std::vector<std::string> buttonLabels = {"Play", "How to Play", "High Scores", "Settings"};
    for (size_t i = 0; i < buttonLabels.size(); ++i) {
        sf::Text buttonText;
        buttonText.setFont(font);
        buttonText.setString(buttonLabels[i]);
        buttonText.setCharacterSize(40);
        buttonText.setFillColor(defaultColor);
        buttonText.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f + i * 65);
        buttonText.setOrigin(buttonText.getLocalBounds().width / 2.0f, buttonText.getLocalBounds().height / 2.0f);
        buttons.push_back(buttonText);

        sf::RectangleShape buttonBackground;
        buttonBackground.setSize(sf::Vector2f(400, 60));
        buttonBackground.setFillColor(sf::Color(0, 0, 0));
        buttonBackground.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f + i * 66 + 5 );
        buttonBackground.setOrigin(buttonBackground.getSize().x / 2.0f, buttonBackground.getSize().y / 2.0f);
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
            } else if (event.key.code == sf::Keyboard::Up){
                SoundManager::getInstance().playSound(SoundID::HOVER);
                selectedButtonIndex = (selectedButtonIndex > 0) ? selectedButtonIndex - 1 : buttons.size() - 1;
            } else if (event.key.code == sf::Keyboard::Down) {
                SoundManager::getInstance().playSound(SoundID::HOVER);
                selectedButtonIndex = (selectedButtonIndex + 1) % buttons.size();
            } else if (event.key.code == sf::Keyboard::Enter) {
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
    auto& stateManager = StateManager::getInstance();
    switch (buttonIndex) {
        case 0:
            stateManager.pushState(std::make_unique<PlayState>());
            break;
        case 1:
            stateManager.pushState(std::make_unique<HowToPlayState>());
            break;
        case 2:
            stateManager.pushState(std::make_unique<HighScoresState>());
            break;
        case 3:
            stateManager.pushState(std::make_unique<SettingsState>());
            break;
        default:
            break;
    }
}

void MenuState::updateButtonStates(const sf::Vector2f& mousePos) {
    for (size_t i = 0; i < buttonBackgrounds.size(); ++i) {
        if (buttonBackgrounds[i].getGlobalBounds().contains(mousePos)) {
            buttons[i].setFillColor(hoverColor);
            selectedButtonIndex = i;
        } else if (i == selectedButtonIndex) {
            buttons[i].setFillColor(hoverColor);
        } else {
            buttons[i].setFillColor(defaultColor);
        }
    }
}
