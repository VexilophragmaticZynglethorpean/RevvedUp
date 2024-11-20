#include "Core/EventManager.h"
#include "Core/Global.h"
#include "States/PlayState.h"
#include "SFML/Window/Event.hpp"
#include <functional>
#include <cstdlib>

#ifdef DEV_PHASE
#include <imgui.h>
#endif

PlayState::PlayState()
  : car()
  , background()
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

    eventManager.addListener(
      StateID::Play, sf::Event::Resized, std::bind(&PlayState::resize, this, std::placeholders::_1));

    eventManager.addListener(
      StateID::Play, sf::Event::Closed, std::bind(&PlayState::exit, this));

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
    auto& window = Global::getWindow();

    window.draw(background);
    window.draw(car);
}

void
PlayState::resize(const sf::Event& event){
  sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
  Global::getWindow().setView(sf::View(visibleArea));
}

void
PlayState::exit()
{
}
