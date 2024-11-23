#include "Core/EventManager.h"
#include "Core/StateManager.h"
#include "Core/WindowManager.h"
#include "States/MenuState.h"
#include <SFML/Graphics.hpp>

int
main()
{
    auto& window = WindowManager::getWindow();
    auto& stateManager = StateManager::getInstance();
    auto& eventManager = EventManager::getInstance();
    sf::Clock deltaClock;

    stateManager.pushState(std::make_unique<MenuState>());

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            eventManager.handleEvent(stateManager.getCurrentStateID(), event);
        }

        stateManager.update(deltaClock.restart());

        window.clear(sf::Color::Black);
        stateManager.render(window);
        window.display();
    }

    return EXIT_SUCCESS;
}
