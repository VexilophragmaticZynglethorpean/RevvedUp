#include "SFML/Graphics/RenderStates.hpp"
#include <glad/gl.h>
#include <Core/Global.h>
#include <Util/Path.h>
#include <States/PlayState.h>
#include <Core/StateManager.h>
#include <Core/EventManager.h>

#include <cstdlib>
#include <filesystem>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#ifdef DEV_PHASE
#include <imgui.h>
#endif

PlayState::PlayState() : car(), cube(), camera() {
    id = StateID::Play;
}

void PlayState::init() {
    auto t_start = std::chrono::high_resolution_clock::now();

    auto assetsDir = Util::getExecutablePath() / "assets";
    auto shadersDir = Util::getExecutablePath() / "shaders";

    auto& textureAtlas = Global::getTexture();
    textureAtlas.loadFromFile(assetsDir / "red.jpg");
    textureAtlas.setSmooth(true);

    auto& shader = Global::getShader();
    shader.loadFromFile(
        shadersDir / "cube.vert",
        shadersDir / "cube.geo",
        shadersDir / "cube.frag"
    );
    shader.setUniform("texture", textureAtlas);

    camera.setPosition(glm::vec3(0.0f, 0.0f, 0.0f))
          .setTarget(glm::vec3(1.5f, 1.5f, 2.0f))
          .setUp(glm::vec3(0.0f, 0.0f, 1.0f))
          .setProjection(ProjectionType::Perspective)
          .setFOV(45.0f)
          .setNearFar(1.0f, 10.0f)
          .setAspectRatio()
          .update();

    /*car.init();*/
    cube.init(true);

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

    eventManager.addListener(
        StateID::Play,
        sf::Event::Resized,
        std::bind(&PlayState::resize, this)
    );
}

void PlayState::update(const sf::Time& deltaTime) {
    /*car.update(deltaTime);*/

    auto t_now = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(
        model,
        0.25f * time * glm::radians(180.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)
    );

    /*glm::mat4 mvp = camera.getVP() * cube.getTransform();*/
    glm::mat4 mvp = camera.getVP() * model;

    auto mvp_ptr = glm::value_ptr(mvp);
    auto& shader = Global::getShader();
    shader.setUniform("ModelViewProjection", sf::Glsl::Mat4(mvp_ptr));

}

void PlayState::render() {
    /*window->draw(car);*/

    #ifdef DEV_PHASE
    ImGui::Begin("Camera Controls");
    static float x = 0.0f;
    static float y = 0.0f;
    static float z = 0.0f;
    ImGui::DragFloat("x", &x);
    ImGui::DragFloat("y", &y);
    ImGui::DragFloat("z", &z);
    camera.setPosition(glm::vec3(x, y, z));
    ImGui::End();
    #endif

    sf::RenderStates renderStates;
    renderStates.shader = &Global::getShader();
    renderStates.texture = &Global::getTexture();

    Global::getWindow().draw(cube, renderStates);
}

void PlayState::resize() {
    Global::getWindow().setActive();
    glViewport(0, 0, Global::getWindow().getSize().x, Global::getWindow().getSize().y);
    Global::getWindow().setActive(false);

    camera.updateProjectionMatrix();
}

void PlayState::exit() {
}

