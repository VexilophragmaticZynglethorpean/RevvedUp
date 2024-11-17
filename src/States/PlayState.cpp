#include <States/PlayState.h>
#include <Core/StateManager.h>
#include <Core/EventManager.h>
#include <Util/Path.h>

#include <cstdlib>
#include <filesystem>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#ifdef DEV_PHASE
#include <imgui.h>
#endif

PlayState::PlayState() : car(), cube(), camera(), textureAtlas(std::make_shared<sf::Texture>()) {
    id = StateID::Play;
}

void PlayState::update(std::shared_ptr <const sf::RenderWindow> window, const sf::Time& deltaTime) {
    car.update(window, deltaTime);
}

void PlayState::render(std::shared_ptr <sf::RenderTarget> window) {
    /*window->draw(car);*/

    #ifdef DEV_PHASE
    ImGui::Begin("Cube Transformation");

    // Position controls
    ImGui::Text("Position");
    float pos[3] = { cube.getPosition().x, cube.getPosition().y, cube.getPosition().z };
    if (ImGui::InputFloat3("Position", pos)) {
        cube.setPosition(pos[0], pos[1], pos[2]);
    }

    // Rotation controls
    ImGui::Text("Rotation (degrees)");
    glm::vec3 rot = glm::degrees(glm::eulerAngles(cube.getRotation())); // Convert to degrees
    if (ImGui::InputFloat3("Rotation", &rot[0])) {
        // Set the rotation using the new Euler angles
        cube.setRotation(rot.x, glm::vec3(1, 0, 0)); // Rotate around X
        cube.setRotation(rot.y, glm::vec3(0, 1, 0)); // Rotate around Y
        cube.setRotation(rot.z, glm::vec3(0, 0, 1)); // Rotate around Z
    }

    // Scale controls
    ImGui::Text("Scale");
    float scale[3] = { cube.getScale().x, cube.getScale().y, cube.getScale().z };
    if (ImGui::InputFloat3("Scale", scale)) {
        cube.setScale(scale[0], scale[1], scale[2]);
    }

    ImGui::End();
    #endif

    glm::mat4 mvp = camera.getVP() * cube.getTransform();

    auto mvp_ptr = glm::value_ptr(mvp);
    shader.setUniform("ModelViewProjection", sf::Glsl::Mat4(mvp_ptr));
    window->draw(cube, &shader);
}

void PlayState::init(std::shared_ptr <sf::RenderWindow> window) {
    auto assetsDir = Util::getExecutablePath().parent_path() / "assets";
    auto shadersDir = Util::getExecutablePath().parent_path() / "shaders";

    auto textureAtlasFile = assetsDir / "red.jpg";
    auto vertFile = shadersDir / "default.vert";
    auto fragFile = shadersDir / "default.frag";

    textureAtlas->loadFromFile(textureAtlasFile);
    textureAtlas->setSmooth(true);

    shader.loadFromFile(vertFile.string(), fragFile.string());

    /*car.init(textureAtlas);*/
    cube.init(window, textureAtlas, true);

    EventManager& eventManager = EventManager::getInstance();

    eventManager.addListener(
        StateID::Play,
        sf::Event::KeyPressed,
        std::bind(&Car::handleEvents, &car, std::placeholders::_1)
    );

    eventManager.addListener(
        StateID::Play,
        sf::Event::KeyReleased,
        std::bind(&Car::handleEvents, &car, std::placeholders::_1)
    );

    eventManager.addListener(
        StateID::Play,
        sf::Event::Closed,
        std::bind(&PlayState::exit, this)
    );
}

void PlayState::exit() {
}
