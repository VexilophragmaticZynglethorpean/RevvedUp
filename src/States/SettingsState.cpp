#include "States/SettingsState.h"
#include "Util/Path.h"
#include "Core/StateManager.h"

SettingsState::SettingsState()
: State(StateID::Settings)
{
}

void SettingsState::init() {
    auto& eventManager = EventManager::getInstance();
    auto windowSize = WindowManager::getWindow().getSize();

    font.loadFromFile(Util::getExecutablePath() / "assets/SuperchargeHalftone.otf");

    settingsText.setFont(font);
    settingsText.setString("Settings:\n\nAdjust your game settings here.\nPress ESC to return to menu.");
    settingsText.setCharacterSize(30);
    settingsText.setFillColor(sf::Color::White);
    settingsText.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
    settingsText.setOrigin(settingsText.getLocalBounds().width / 2, settingsText.getLocalBounds().height / 2);

    eventManager.addListener(StateID::Settings, sf::Event::KeyPressed, std::bind(&SettingsState::handleEvents, this, std::placeholders::_1));
    eventManager.addListener(StateID::Settings, sf::Event::Closed, std::bind(&SettingsState::handleEvents, this, std::placeholders::_1));
}

void SettingsState::update(const sf::Time& deltaTime) {
}

void SettingsState::render(sf::RenderTarget& target) {
    target.clear(sf::Color::Black);
    target.draw(settingsText);
}

void SettingsState::exit() {
    auto& eventManager = EventManager::getInstance();
    eventManager.removeAllListeners(StateID::Settings, sf::Event::KeyPressed);
    eventManager.removeAllListeners(StateID::Settings, sf::Event::Closed);
}

void SettingsState::handleEvents(const sf::Event& event) {
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
