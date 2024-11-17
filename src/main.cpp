#include <glad/gl.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <Util/Path.h>
#include <Core/Global.h>

#include <Core/EventManager.h>
#include <Core/StateManager.h>
#include <States/PlayState.h>

#ifdef DEV_PHASE
#include <imgui.h>
#include <imgui-SFML.h>

void handleDebugWindow(std::pair <sf::RenderWindow*, sf::Event*> arg) {

    while (arg.first->isOpen()) {
        while(arg.first->pollEvent(*arg.second)) {

            if (arg.second->type == sf::Event::Closed)
                arg.first->close();
        }
    }
}
#endif

int main() {
    auto& window = Global::getWindow();
    window.setVerticalSyncEnabled(true);

    #ifdef DEV_PHASE
    auto debugWindow = sf::RenderWindow(sf::VideoMode(800, 600), "Debug", sf::Style::None);
    sf::Event debugWindowEvent;

    assert(ImGui::SFML::Init(debugWindow));
    debugWindow.setFramerateLimit(60);
    debugWindow.clear(sf::Color(0, 0, 0, 0));

    std::pair <sf::RenderWindow*, sf::Event*> arg(&debugWindow, &debugWindowEvent);
    sf::Thread thread(&handleDebugWindow, arg);
    thread.launch();
    #endif

    gladLoadGL(sf::Context::getFunction);

    auto& stateManager = StateManager::getInstance();
    auto& eventManager = EventManager::getInstance();
    sf::Clock deltaClock;

    stateManager.pushState(std::make_unique<PlayState>());

    window.setActive();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    window.setActive(false);


    while (window.isOpen()) {

        sf::Event event;
        while(window.pollEvent(event)) {
            eventManager.handleEvent(stateManager.getCurrentStateID(), event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        ImGui::SFML::ProcessEvent(debugWindow, debugWindowEvent);

        stateManager.update(deltaClock.getElapsedTime());
        deltaClock.restart();

        window.setActive();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        window.setActive(false);

        stateManager.render();

        #ifdef DEV_PHASE
        ImGui::SFML::Render(debugWindow);
        #endif

        window.display();

        #ifdef DEV_PHASE
        if (debugWindow.isOpen()) debugWindow.display();
        #endif
    }

    #ifdef DEV_PHASE
    ImGui::SFML::Shutdown();
    #endif

    return EXIT_SUCCESS;
}
//delete from here
