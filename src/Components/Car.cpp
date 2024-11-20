#include "Components/Car.h"
#include "Core/WindowManager.h"
#include "Core/TextureManager.h"
#include <algorithm>

#ifdef DEV_PHASE
#include <imgui-SFML.h>
#include <imgui.h>
#endif

namespace {
static float FORWARD_INCREMENT = 0.1f;
static float BACKWARD_DECREMENT = 0.1f;
static float RIGHT_INCREMENT = 0.1f;
static float LEFT_DECREMENT = 0.1f;

static float DAMPING = 0.1f;
static float MAX_DAMPING = 1.0f;
static float MAX_X_ACCELERATION = 10.0f;
static float MAX_Y_ACCELERATION = 10.0f;
}

Car::Car()
  : forwardVelocity(0.0f)
  , rightVelocity(0.0f)
  ,

  forwardAcceleration(0.0f)
  , rightAcceleration(0.0f)
  ,

  forwardMovement(false)
  , backwardMovement(false)
  , leftMovement(false)
  , rightMovement(false)
{
}

void
Car::handleEvents(const sf::Event& event)
{
    if (event.type == sf::Event::Resized) {
        sprite.setPosition(event.size.width/2.0, event.size.height * 0.9);
        return;
    }

    bool pressed = event.type != sf::Event::KeyReleased;
    bool W_Up =
      event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up;
    bool A_Left =
      event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left;
    bool S_Down =
      event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down;
    bool D_Right = event.key.code == sf::Keyboard::D ||
                   event.key.code == sf::Keyboard::Right;

    forwardMovement = W_Up ? pressed : forwardMovement;
    leftMovement = A_Left ? pressed : leftMovement;
    backwardMovement = S_Down ? pressed : backwardMovement;
    rightMovement = D_Right ? pressed : rightMovement;
}

void
Car::init()
{
    auto& window = WindowManager::getWindow();
    auto& texManager = TextureManager::getInstance();
    sprite.setTexture(texManager.getTexture(TextureManager::JEEP0));

    sprite.scale(0.25, 0.25);

    auto spriteBounds = sprite.getLocalBounds();
    sprite.setOrigin(spriteBounds.width / 2, spriteBounds.height);
}

void
Car::update(const sf::Time& deltaTime)
{
    calcPosition(deltaTime);

#ifdef DEV_PHASE
    ImGui::Begin("Debug");
    // Drag and Input for FORWARD_INCREMENT
    ImGui::DragFloat("FORWARD_INCREMENT", &FORWARD_INCREMENT, 0.001f);
    ImGui::InputFloat("FORWARD_INCREMENT (Input)", &FORWARD_INCREMENT);

    // Drag and Input for BACKWARD_DECREMENT
    ImGui::DragFloat("BACKWARD_DECREMENT", &BACKWARD_DECREMENT, 0.001f);
    ImGui::InputFloat("BACKWARD_DECREMENT (Input)", &BACKWARD_DECREMENT);

    // Drag and Input for RIGHT_INCREMENT
    ImGui::DragFloat("RIGHT_INCREMENT", &RIGHT_INCREMENT, 0.001f);
    ImGui::InputFloat("RIGHT_INCREMENT (Input)", &RIGHT_INCREMENT);

    // Drag and Input for LEFT_DECREMENT
    ImGui::DragFloat("LEFT_DECREMENT", &LEFT_DECREMENT, 0.001f);
    ImGui::InputFloat("LEFT_DECREMENT (Input)", &LEFT_DECREMENT);

    // Drag and Input for DAMPING
    ImGui::DragFloat("DAMPING", &DAMPING, 0.001f);
    ImGui::InputFloat("DAMPING (Input)", &DAMPING);

    // Drag and Input for MAX_DAMPING
    ImGui::DragFloat("MAX_DAMPING", &MAX_DAMPING, 0.001f);
    ImGui::InputFloat("MAX_DAMPING (Input)", &MAX_DAMPING);

    // Drag and Input for MAX_X_ACCELERATION
    ImGui::DragFloat("MAX_X_ACCELERATION", &MAX_X_ACCELERATION, 0.001f);
    ImGui::InputFloat("MAX_X_ACCELERATION (Input)", &MAX_X_ACCELERATION);

    // Drag and Input for MAX_Y_ACCELERATION
    ImGui::DragFloat("MAX_Y_ACCELERATION", &MAX_Y_ACCELERATION, 0.001f);
    ImGui::InputFloat("MAX_Y_ACCELERATION (Input)", &MAX_Y_ACCELERATION);
#endif
}

void
Car::calcAcceleration()
{
    if (forwardMovement)
        forwardAcceleration += FORWARD_INCREMENT;
    if (backwardMovement)
        forwardAcceleration -= BACKWARD_DECREMENT;
    if (!forwardMovement && !backwardMovement)
        forwardAcceleration = 0.0f;

    forwardAcceleration =
      std::clamp(forwardAcceleration, -MAX_Y_ACCELERATION, MAX_Y_ACCELERATION);

    if (rightMovement)
        rightAcceleration += RIGHT_INCREMENT;
    if (leftMovement)
        rightAcceleration -= LEFT_DECREMENT;
    if (!rightMovement && !leftMovement)
        rightAcceleration = 0.0f;

    rightAcceleration =
      std::clamp(rightAcceleration, -MAX_X_ACCELERATION, MAX_X_ACCELERATION);
}

void
Car::calcVelocity(const sf::Time& deltaTime)
{
    calcAcceleration();

    float dt = deltaTime.asSeconds();

    forwardVelocity +=
      forwardAcceleration
        ? forwardAcceleration * dt
        : -forwardVelocity * std::min(MAX_DAMPING, DAMPING * dt);

    rightVelocity =
      rightAcceleration ? rightVelocity + rightAcceleration * dt : 0.0f;
}

void
Car::calcPosition(const sf::Time& deltaTime)
{
    calcVelocity(deltaTime);

    float dt = deltaTime.asSeconds();

    float xOffset = rightVelocity * dt;

    auto windowSize = WindowManager::getWindow().getSize();

    sf::Vector2f oldPosition = sprite.getPosition();
    sf::FloatRect windowBounds(0, 0, windowSize.x, windowSize.y);

    sprite.move(xOffset, 0);

    if (intersectsBoundaries(windowBounds))
        sprite.setPosition(oldPosition);
}

bool
Car::intersectsBoundaries(const sf::FloatRect& boundary)
{
    auto spriteBounds = sprite.getGlobalBounds();

    auto boundaryLeft = sf::FloatRect(0, 0, 1, boundary.getSize().y);
    auto boundaryRight =
      sf::FloatRect(boundary.getSize().x - 1, 0, 1, boundary.getSize().y);
    auto boundaryTop = sf::FloatRect(0, 0, boundary.getSize().x, 1);
    auto boundaryBottom = sf::FloatRect(
      0, boundary.getSize().y - 1, boundary.getSize().x, boundary.getSize().y);

    if (boundaryLeft.intersects(spriteBounds) ||
        boundaryRight.intersects(spriteBounds) ||
        boundaryTop.intersects(spriteBounds) ||
        boundaryBottom.intersects(spriteBounds)) {
        return true;
    }
    return false;
}

void
Car::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite);
}
