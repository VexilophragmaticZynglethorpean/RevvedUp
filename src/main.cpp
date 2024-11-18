#include <glad/gl.h>
#include <SFML/OpenGL.hpp>
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
#endif

int main() {
	auto& window = Global::getWindow();

#ifdef DEV_PHASE
	auto debugWindow = sf::RenderWindow(sf::VideoMode(100, 100), "Debug");
	sf::Event debugWindowEvent;

	assert(ImGui::SFML::Init(debugWindow));
	debugWindow.setFramerateLimit(60);
#endif

	gladLoadGL(sf::Context::getFunction);

	auto& stateManager = StateManager::getInstance();
	auto& eventManager = EventManager::getInstance();
	sf::Clock deltaClock;

	Global::getClock();

	stateManager.pushState(std::make_unique<PlayState>());
 
    /*glEnable(GL_DEPTH_TEST);*/
    /*glDepthFunc(GL_LESS);*/
    /*glEnable(GL_BLEND);*/
    /*glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			eventManager.handleEvent(stateManager.getCurrentStateID(), event);

			if (event.type == sf::Event::Closed) {
				window.close();
#ifdef DEV_PHASE
				debugWindow.close();
#endif
			}
	}

#ifdef DEV_PHASE
		while (debugWindow.pollEvent(debugWindowEvent)) {
			ImGui::SFML::ProcessEvent(debugWindow, debugWindowEvent);
			if (debugWindowEvent.type == sf::Event::Closed) {
				debugWindow.close();
			}
		}
		ImGui::NewFrame();
#endif

		stateManager.update(deltaClock.getElapsedTime());
		deltaClock.restart();
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0, 1.0, 1.0, 1.0);

		stateManager.render();

#ifdef DEV_PHASE
		debugWindow.clear(sf::Color::Black);
		ImGui::SFML::Render(debugWindow);
		ImGui::EndFrame();
		if (debugWindow.isOpen()) debugWindow.display();
#endif

		window.display();
	}

#ifdef DEV_PHASE
	ImGui::SFML::Shutdown();
#endif

	return EXIT_SUCCESS;
}

