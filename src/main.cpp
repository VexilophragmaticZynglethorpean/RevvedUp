#include <SFML/Graphics.hpp>
#include "Core/WindowManager.h"
#include "Core/EventManager.h"
#include "Core/StateManager.h"
#include "States/PlayState.h"

#ifdef DEV_PHASE
#include <imgui-SFML.h>
#include <imgui.h>
#endif

int
main()
{
    auto& window = WindowManager::getWindow();

#ifdef DEV_PHASE
    assert(ImGui::SFML::Init(window));
#endif

    auto& stateManager = StateManager::getInstance();
    auto& eventManager = EventManager::getInstance();
    sf::Clock deltaClock;

    WindowManager::getClock();

    stateManager.pushState(std::make_unique<PlayState>());

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            eventManager.handleEvent(stateManager.getCurrentStateID(), event);

#ifdef DEV_PHASE
            ImGui::SFML::ProcessEvent(window, event);
#endif

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

#ifdef DEV_PHASE
        ImGui::NewFrame();
#endif

        stateManager.update(deltaClock.getElapsedTime());
        deltaClock.restart();

        window.clear(sf::Color::Black);

        stateManager.render(window);

#ifdef DEV_PHASE
        ImGui::SFML::Render(window);
        ImGui::EndFrame();
#endif

        window.display();
    }

#ifdef DEV_PHASE
    ImGui::SFML::Shutdown();
#endif

    return EXIT_SUCCESS;
}
