#include <glad/gl.h>
#include <SFML/Graphics.hpp>

#include <Core/EventManager.h>
#include <Core/StateManager.h>
#include <Util/Path.h>

#include <States/PlayState.h>

#ifdef DEV_PHASE
#include <imgui.h>
#include <imgui-SFML.h>
#endif

int main() {

    #ifdef DEV_PHASE
    auto window = std::make_shared <sf::RenderWindow>(sf::VideoMode(800, 600), "RevvedUp");
    #else
    auto window = std::make_shared <sf::RenderWindow>(sf::VideoMode(800, 600), "RevvedUp");
    #endif

    gladLoadGL(reinterpret_cast<GLADloadfunc>(sf::Context::getFunction));

    #ifdef DEV_PHASE
    assert(ImGui::SFML::Init(*window));
    #endif


    StateManager& stateManager = StateManager::getInstance();
    EventManager& eventManager = EventManager::getInstance();
    sf::Clock deltaClock;

    stateManager.pushState(window, std::make_unique<PlayState>());

    while (window->isOpen()) {

        sf::Event event;
        while(window->pollEvent(event)) {

            #ifdef DEV_PHASE
            ImGui::SFML::ProcessEvent(*window, event);
            #endif

            eventManager.handleEvent(stateManager.getCurrentStateID(), event);

            if (event.type == sf::Event::Closed && window)
                window->close();
        }

        #ifdef DEV_PHASE
        ImGui::SFML::Update(*window, deltaClock.getElapsedTime());
        #endif

        stateManager.update(window, deltaClock.getElapsedTime());
        deltaClock.restart();

        window->clear(sf::Color::White);

        stateManager.render(window);

        #ifdef DEV_PHASE
        ImGui::SFML::Render(*window);
        #endif

        window->display();
    }

    #ifdef DEV_PHASE
    ImGui::SFML::Shutdown();
    #endif

    return EXIT_SUCCESS;
}
