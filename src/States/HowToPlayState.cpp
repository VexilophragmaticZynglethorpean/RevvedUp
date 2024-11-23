#include "States/HowToPlayState.h"
#include "Util/Path.h"
#include "Core/StateManager.h"

HowToPlayState::HowToPlayState()
: State(StateID::HowToPlay)
{
}

void HowToPlayState::init() {
    auto& eventManager = EventManager::getInstance();
    auto windowSize = WindowManager::getWindow().getSize();

    font.loadFromFile(Util::getExecutablePath() / "assets/SuperchargeHalftone.otf");

    instructionsText.setFont(font);
    instructionsText.setString("Instructions:\n\nUse arrow keys to move.\nAvoid obstacles.\nPress ESC to return to menu.");
    instructionsText.setCharacterSize(30);
    instructionsText.setFillColor(sf::Color::White);
    instructionsText.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
    instructionsText.setOrigin(instructionsText.getLocalBounds().width / 2, instructionsText.getLocalBounds().height / 2);

    eventManager.addListener(StateID::HowToPlay, sf::Event::KeyPressed, std::bind(&HowToPlayState::handleEvents, this, std::placeholders::_1));
    eventManager.addListener(StateID::HowToPlay, sf::Event::Closed, std::bind(&HowToPlayState::handleEvents, this, std::placeholders::_1));
}

void HowToPlayState::update(const sf::Time& deltaTime) {
}

void HowToPlayState::render(sf::RenderTarget& target) {
    target.clear(sf::Color::Black);
    target.draw(instructionsText);
}

void HowToPlayState::exit() {
    auto& eventManager = EventManager::getInstance();
    eventManager.removeAllListeners(StateID::HowToPlay, sf::Event::KeyPressed);
    eventManager.removeAllListeners(StateID::HowToPlay, sf::Event::Closed);
}

void HowToPlayState::handleEvents(const sf::Event& event) {
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
