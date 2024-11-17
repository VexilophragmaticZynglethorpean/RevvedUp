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

void PlayState::update(const sf::Time& deltaTime) {
    car.update(deltaTime);
}

void PlayState::render() {
    /*window->draw(car);*/

    /*#ifdef DEV_PHASE*/
    /*ImGui::Begin("Cube Transformation");*/
    /*ImGui::Text("hi");*/
    /*ImGui::End();*/
    /*#endif*/

    glm::mat4 mvp = camera.getVP() * cube.getTransform();

    auto mvp_ptr = glm::value_ptr(mvp);
    auto& shader = Global::getShader();
    shader.setUniform("ModelViewProjection", sf::Glsl::Mat4(mvp_ptr));
    Global::getWindow().draw(cube, &shader);
}

void PlayState::init() {
    auto assetsDir = Util::getExecutablePath().parent_path() / "assets";
    auto shadersDir = Util::getExecutablePath().parent_path() / "shaders";

    auto& textureAtlas = Global::getTexture();
    textureAtlas.loadFromFile(assetsDir / "red.jpg");
    textureAtlas.setSmooth(true);

    auto& shader = Global::getShader();
    shader.loadFromFile(shadersDir / "default.vert", shadersDir / "default.frag");
    shader.setUniform("texture", textureAtlas);

    camera.updateProjectionMatrix(ProjectionType::Perspective);

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
}

void PlayState::exit() {
}
