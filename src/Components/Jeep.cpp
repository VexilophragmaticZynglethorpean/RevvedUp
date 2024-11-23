/*#include "Components/Jeep.h"*/
/*#include "Core/TextureManager.h"*/
/*#include "Core/WindowManager.h"*/
/*#include <cmath>*/
/*#include <random>*/
/**/
/*#ifdef DEV_PHASE*/
/*#include <imgui.h>*/
/*#endif*/
/**/
/*constexpr float LERP_SPEED_CONST = 0.1f;*/
/*constexpr float INITIAL_SCALE_X = 0.1f;*/
/*constexpr float INITIAL_SCALE_Y = 0.1f;*/
/*constexpr float MAX_ROTATION = 15.0f;*/
/*constexpr float SCALE_SPEED = 0.2f;*/
/**/
/*Jeep::Jeep(sf::Vector2f spawnPoint,*/
/*           sf::Vector2f endPosition,*/
/*           float forwardVelocity,*/
/*           sf::Vector2f fullScale)*/
/*  : Car(forwardVelocity, spawnPoint)*/
/*  , endPosition(endPosition)*/
/*  , fullScale(fullScale)*/
/*  , dt(0.0f)*/
/*{*/
/*}*/
/**/
/*sf::Vector2f*/
/*Jeep::lerp(const sf::Vector2f& start, const sf::Vector2f& end, float t)*/
/*{*/
/*    t = std::clamp(t, 0.0f, 1.0f);*/
/*    return start + (end - start) * t * t;*/
/*}*/
/**/
/*float*/
/*Jeep::lerp(float start, float end, float t)*/
/*{*/
/*    t = std::clamp(t, 0.0f, 1.0f);*/
/*    return start + (end - start) * t * t;*/
/*}*/
/**/
/*float*/
/*Jeep::terp(float start, float end, float t)*/
/*{*/
/*    t = std::clamp(t, 0.0f, 2.0f);*/
/*    return (t <= 1.0f) ? lerp(start, end, t) : lerp(start, end, 2.5f - t);*/
/*}*/
/**/
/*void*/
/*Jeep::init()*/
/*{*/
/*    std::random_device rd;*/
/*    std::mt19937 eng(rd());*/
/*    std::uniform_int_distribution<> distr(0, 1);*/
/**/
/*    auto& tex = TextureManager::getInstance().getTexture(TextureID::JEEP);*/
/*    auto windowSize = WindowManager::getWindow().getSize();*/
/**/
/*    sf::IntRect rect;*/
/*    rect.left = distr(eng) * (tex.getSize().x / 2);*/
/*    rect.top = 0;*/
/*    rect.width = tex.getSize().y;*/
/*    rect.height = tex.getSize().y;*/
/**/
/*    sprite.setTexture(tex);*/
/*    sprite.setTextureRect(rect);*/
/*    sprite.setOrigin(tex.getSize().x / 2.0f, tex.getSize().y);*/
/*    sprite.setPosition(positionPercentage.x * windowSize.x,*/
/*                       positionPercentage.y * windowSize.y);*/
/*    sprite.setScale(INITIAL_SCALE_X, INITIAL_SCALE_Y);*/
/*}*/
/*sf::Vector2f*/
/*Jeep::getPosition() const*/
/*{*/
/*    return positionPercentage;*/
/*}*/
/**/
/*void*/
/*Jeep::update(const sf::Time& deltaTime)*/
/*{*/
/*    dt += LERP_SPEED_CONST * forwardVelocity * deltaTime.asSeconds();*/
/*    auto nextPosition = lerp(positionPercentage, endPosition, dt);*/
/*    auto currentScale = sprite.getScale();*/
/**/
/*    auto windowSize = WindowManager::getWindow().getSize();*/
/*    sprite.setPosition(nextPosition.x * windowSize.x,*/
/*                       nextPosition.y * windowSize.y);*/
/*    sprite.setScale(lerp(currentScale, fullScale, SCALE_SPEED * dt));*/
/*    sprite.setRotation(lerp(0.0f, MAX_ROTATION, 0.2f * dt));*/
/*    sprite.setColor(*/
/*      sf::Color(255, 255, 255, static_cast<sf::Uint8>(terp(0, 255, 2 *
 * dt))));*/
/*#ifdef DEV_PHASE*/
/*    ImGui::Begin("JEEP");*/
/*    ImGui::Text("Current scale %f %f", currentScale.x, currentScale.y);*/
/*    ImGui::Text("Full scale %f %f", fullScale.x, fullScale.y);*/
/*    ImGui::Text("Next pos %f %f", nextPosition.x, nextPosition.y);*/
/*    ImGui::Text(*/
/*      "Position %f, %f", sprite.getPosition().x, sprite.getPosition().y);*/
/*    ImGui::Text("Scale %f, %f", sprite.getScale().x, sprite.getScale().y);*/
/*    ImGui::Text("Angle %f", sprite.getRotation());*/
/*    ImGui::Text("Color %u %u %u %u",*/
/*                sprite.getColor().r,*/
/*                sprite.getColor().g,*/
/*                sprite.getColor().b,*/
/*                sprite.getColor().a);*/
/*    ImGui::End();*/
/**/
/*    ImGui::Begin("Debug");*/
/*    sf::Vector2i mouse = sf::Mouse::getPosition(WindowManager::getWindow());*/
/*    sf::Vector2u size = WindowManager::getWindow().getSize();*/
/*    ImGui::Text("%f %f",*/
/*                static_cast<float>(mouse.x) / size.x,*/
/*                static_cast<float>(mouse.y) / size.y);*/
/*    ImGui::Text("%d %d", mouse.x, mouse.y);*/
/*    ImGui::End();*/
/*#endif*/
/*}*/
/**/
/*void*/
/*Jeep::draw(sf::RenderTarget& target, sf::RenderStates states) const*/
/*{*/
/*    target.draw(sprite);*/
/*}*/
