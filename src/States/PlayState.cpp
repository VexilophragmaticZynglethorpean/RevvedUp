#include "Core/EventManager.h"
#include "Core/Global.h"
#include "States/PlayState.h"
#include "Util/Path.h"
#include <glad/gl.h>

#include <cstdlib>
#include <filesystem>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#ifdef DEV_PHASE
#include <imgui.h>
#endif

PlayState::PlayState()
  : car()
  , cube()
  , camera()
  , background(11, 5, 55)
{
    id = StateID::Play;
}

void
PlayState::init()
{
    auto assetsDir = Util::getExecutablePath() / "assets";
    /*auto shadersDir = Util::getExecutablePath() / "shaders";*/

    /*auto& shader = Global::getShader();*/
    /*shader.loadFromFile(shadersDir / "default.vert",*/
    /*                    shadersDir / "default.frag");*/
    /*shader.setUniform("texture", textureAtlas);*/
    /*sf::Shader::bind(&shader);*/

    /*camera.setPosition(glm::vec3(0.0f, 0.0f, 0.0f))*/
    /*  .setTarget(glm::vec3(1.5f, 1.5f, 2.0f))*/
    /*  .setUp(glm::vec3(0.0f, 0.0f, 1.0f))*/
    /*  .setProjection(ProjectionType::Perspective)*/
    /*  .setFOV(45.0f)*/
    /*  .setNearFar(1.0f, 10.0f)*/
    /*  .setAspectRatio()*/
    /*  .update();*/

    background.init();
    /*cube.init();*/
    car.init();

    EventManager& eventManager = EventManager::getInstance();

    eventManager.addListener(
      StateID::Play,
      sf::Event::KeyPressed,
      std::bind(&Car::handleEvents, &car, std::placeholders::_1));

    eventManager.addListener(
      StateID::Play,
      sf::Event::KeyReleased,
      std::bind(&Car::handleEvents, &car, std::placeholders::_1));

    eventManager.addListener(
      StateID::Play, sf::Event::Closed, std::bind(&PlayState::exit, this));

    /*eventManager.addListener(*/
      /*StateID::Play, sf::Event::Resized, std::bind(&PlayState::resize, this));*/
}

void
PlayState::update(const sf::Time& deltaTime)
{
    car.update(deltaTime);
    background.update(deltaTime, car);

    /*glm::mat4 model = glm::mat4(1.0f);*/
    /*model =*/
    /*  glm::rotate(model,*/
    /*              0.25f * Global::getClock().getElapsedTime().asSeconds() **/
    /*                glm::radians(180.0f),*/
    /*              glm::vec3(0.0f, 0.0f, 1.0f));*/
    /**/
    /*glm::mat4 view = glm::lookAt(glm::vec3(1.5f, 1.5f, 2.0f),*/
    /*                             glm::vec3(0.0f, 0.0f, 0.0f),*/
    /*                             glm::vec3(0.0f, 0.0f, 1.0f));*/
    /*glm::mat4 proj =*/
    /*  glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 10.0f);*/
    /**/
    /*auto mvp_ptr = glm::value_ptr(proj * view * model);*/
    /*auto& shader = Global::getShader();*/
    /*shader.setUniform("ModelViewProjection", sf::Glsl::Mat4(mvp_ptr));*/
}

void
PlayState::render()
{
    /*sf::RenderStates renderStates;*/
    /*renderStates.shader = &Global::getShader();*/
    /*renderStates.texture = ();*/

    auto& window = Global::getWindow();

    /*window.draw(cube, renderStates);*/

    /*window.pushGLStates();*/
    /*window.resetGLStates();*/
    window.draw(background);
    window.draw(car);

    /*window.popGLStates();*/
}

void
PlayState::resize()
{
    /*glViewport(*/
    /*  0, 0, Global::getWindow().getSize().x, Global::getWindow().getSize().y);*/
    /**/
    /*camera.updateProjectionMatrix();*/
}

void
PlayState::exit()
{
}
