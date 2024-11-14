#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Shader Example");
    ImGui::SFML::Init(window);

    sf::VertexArray triangle(sf::Triangles, 3);
    triangle[0] = sf::Vertex(sf::Vector2f(400, 100), sf::Color::Red);
    triangle[1] = sf::Vertex(sf::Vector2f(300, 500), sf::Color::Green);
    triangle[2] = sf::Vertex(sf::Vector2f(500, 500), sf::Color::Blue);

    sf::Clock deltaClock;

    while (window.isOpen()) {

        sf::Event event;
        while(window.pollEvent(event)) {

            ImGui::SFML::ProcessEvent(window, event);

            switch (event.type) {
            case sf::Event::Closed:
                window.close();
            default:
                static int a = 2;
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::ShowDemoWindow();

        ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();

        window.clear();
        window.draw(triangle);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
