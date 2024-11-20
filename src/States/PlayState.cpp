#include "Core/EventManager.h"
#include "Core/WindowManager.h"
#include "States/PlayState.h"
#include "SFML/Window/Event.hpp"
#include "Util/Path.h"
#include <functional>
#include <cstdlib>

#ifdef DEV_PHASE
#include <imgui.h>
#endif

PlayState::PlayState()
  : car()
  , background()
  , soundBuffers(3)
  , sound()
{
    id = StateID::Play;
}

void
PlayState::init()
{
    background.init();
    car.init();
    background.changeAtlas(TextureManager::TextureID::ATLAS1);

    EventManager& eventManager = EventManager::getInstance();

    eventManager.addListener(
      StateID::Play, sf::Event::Resized, std::bind(&WindowManager::resizeWindow, std::placeholders::_1));

    eventManager.addListener(
      StateID::Play, sf::Event::KeyPressed, std::bind(&WindowManager::toggleFullScreen, std::placeholders::_1));

    eventManager.addListener(
      StateID::Play, sf::Event::Closed, std::bind(&PlayState::exit, this));

    eventManager.addListener(
      StateID::Play,
      sf::Event::KeyPressed,
      std::bind(&Car::handleEvents, &car, std::placeholders::_1));

    eventManager.addListener(
      StateID::Play,
      sf::Event::KeyReleased,
      std::bind(&Car::handleEvents, &car, std::placeholders::_1));

    eventManager.addListener(
      StateID::Play, sf::Event::Resized, std::bind(&Car::handleEvents, &car, std::placeholders::_1));

    eventManager.addListener(
      StateID::Play, sf::Event::Resized, std::bind(&Background::handleEvents, &background, std::placeholders::_1));


    soundBuffers[0].loadFromFile(Util::getExecutablePath() / "assets/three.wav");
    soundBuffers[1].loadFromFile(Util::getExecutablePath() / "assets/two.wav");
    soundBuffers[2].loadFromFile(Util::getExecutablePath() / "assets/one.wav");
}

void
PlayState::update(const sf::Time& deltaTime)
{
    car.update(deltaTime);
    background.update(deltaTime, car);
}

void
PlayState::render()
{
    auto& window = WindowManager::getWindow();

    window.draw(background);
    window.draw(car);
}

void
PlayState::exit()
{
}
