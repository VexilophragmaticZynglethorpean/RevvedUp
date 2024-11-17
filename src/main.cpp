#include <glad/gl.h>
#include <SFML/Graphics.hpp>

#include <Util/Path.h>
#include <Core/Global.h>

#include <Core/EventManager.h>
#include <Core/StateManager.h>
#include <States/PlayState.h>

#ifdef DEV_PHASE
#include <imgui.h>
#include <imgui-SFML.h>
#endif

int main() {
    auto& window = Global::getWindow();
    window.setVerticalSyncEnabled(true);

    gladLoadGL(sf::Context::getFunction);

    #ifdef DEV_PHASE
    assert(ImGui::SFML::Init(window));
    #endif


    auto& stateManager = StateManager::getInstance();
    auto& eventManager = EventManager::getInstance();
    sf::Clock deltaClock;

    stateManager.pushState(std::make_unique<PlayState>());

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (window.isOpen()) {

        sf::Event event;
        while(window.pollEvent(event)) {

            #ifdef DEV_PHASE
            ImGui::SFML::ProcessEvent(window, event);
            #endif

            eventManager.handleEvent(stateManager.getCurrentStateID(), event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        #ifdef DEV_PHASE
        ImGui::SFML::Update(window, deltaClock.getElapsedTime());
        #endif

        stateManager.update(deltaClock.getElapsedTime());
        deltaClock.restart();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        stateManager.render();

        #ifdef DEV_PHASE
        ImGui::Begin("hi");
        ImGui::Text("adsas");
        ImGui::End();
        ImGui::SFML::Render(window);
        #endif

        window.display();
    }

    #ifdef DEV_PHASE
    ImGui::SFML::Shutdown();
    #endif

    return EXIT_SUCCESS;
}
//delete from here
