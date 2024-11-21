#include "Core/EventManager.h"
#include "Core/TextureManager.h"
#include "Core/WindowManager.h"
#include "Core/StateManager.h"
#include "Core/SoundManager.h"
#include "States/PlayState.h"
#include "States/PauseState.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Util/Path.h"
#include "SFML/Window/Event.hpp"
#include <functional>
#include <cstdlib>
#include <memory>

#ifdef DEV_PHASE
#include <imgui.h>
#endif

PlayState::PlayState()
    : State(StateID::Play)
  , car()
  , background()
{
}

void
PlayState::init()
{
    auto& eventManager = EventManager::getInstance();
    auto& soundManager = SoundManager::getInstance();
    auto& textureManager = TextureManager::getInstance();

    textureManager.loadTexture(TextureID::ATLAS0, Util::getExecutablePath() / "assets/atlas0.png");
    textureManager.loadTexture(TextureID::ATLAS1, Util::getExecutablePath() / "assets/atlas1.png");
    textureManager.loadTexture(TextureID::ATLAS2, Util::getExecutablePath() / "assets/atlas2.png");
    textureManager.loadTexture(TextureID::CAR0, Util::getExecutablePath() / "assets/car0.png");

    soundManager.loadSound(SoundID::THREE, Util::getExecutablePath() / "assets/three.wav");
    soundManager.loadSound(SoundID::TWO, Util::getExecutablePath() / "assets/two.wav");
    soundManager.loadSound(SoundID::ONE, Util::getExecutablePath() / "assets/one.wav");
    soundManager.loadSound(SoundID::GO, Util::getExecutablePath() / "assets/go.wav");

    soundManager.getMusic().openFromFile(Util::getExecutablePath() / "assets/music.ogg");
    soundManager.getMusic().setLoop(true);

    eventManager.addListener(
      StateID::Play, sf::Event::Resized, std::bind(&WindowManager::resizeWindow, std::placeholders::_1));

    eventManager.addListener(
      StateID::Play, sf::Event::KeyPressed, std::bind(&WindowManager::toggleFullScreen, std::placeholders::_1));

    eventManager.addListener(
      StateID::Play, sf::Event::Closed, std::bind(&PlayState::handleEvents, this, std::placeholders::_1));


    eventManager.addListener(
      StateID::Play, sf::Event::KeyPressed, std::bind(&PlayState::handleEvents, this, std::placeholders::_1));

    eventManager.addListener(
      StateID::Play,
      sf::Event::KeyPressed,
      std::bind(&PlayerCar::handleEvents, &car, std::placeholders::_1));

    eventManager.addListener(
      StateID::Play,
      sf::Event::KeyReleased,
      std::bind(&PlayerCar::handleEvents, &car, std::placeholders::_1));

    eventManager.addListener(
      StateID::Play, sf::Event::Resized, std::bind(&PlayerCar::handleEvents, &car, std::placeholders::_1));

    eventManager.addListener(
      StateID::Play, sf::Event::Resized, std::bind(&Background::handleEvents, &background, std::placeholders::_1));

    background.init();
    car.init();

    soundManager.playSound(SoundID::THREE);
    soundManager.playSound(SoundID::TWO);
    soundManager.playSound(SoundID::ONE);
    soundManager.playSound(SoundID::GO);

    soundManager.getMusic().play();
}

void
PlayState::update(const sf::Time& deltaTime)
{
    car.update(deltaTime);
    background.update(deltaTime, car);
}

void
PlayState::render(sf::RenderTarget& target)
{
    target.draw(background);
    target.draw(car);
}

void PlayState::snapshot(sf::RenderTexture& renderTexture) {
    auto windowSize = WindowManager::getWindow().getSize();
    renderTexture.create(windowSize.x, windowSize.y);
    render(renderTexture);
    renderTexture.display();
}

void PlayState::handleEvents(const sf::Event& event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            switch (event.key.code) {
                case sf::Keyboard::Escape:
                    snapshot(TextureManager::getInstance().getRenderTexture());
                    StateManager::getInstance().pushState(std::make_unique<PauseState>());
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

void
PlayState::exit()
{
}
