#include "Components/PlayerCar.h"
#include "Core/WindowManager.h"
#include "Core/TextureManager.h"
#include "SFML/System/Vector2.hpp"
#include <algorithm>

#ifdef DEV_PHASE
#include <imgui-SFML.h>
#include <imgui.h>
#endif

namespace {
static float FORWARD_INCREMENT = 0.1f;
static float BACKWARD_DECREMENT = 0.1f;
static float SIDE_INCREMENT = 0.1f;
static float SIDE_SPEED_MULTIPLIER_CONST = 5.0f;

static float DAMPING = 0.03f;
static float MAX_DAMPING = 1.0f;
static float MAX_VELOCITY = 5.0f;

static float INITIAL_POSITION_X = 0.5f;
static float INITIAL_POSITION_Y = 0.9f;
static float INITIAL_SCALE_X = 0.2f;
static float INITIAL_SCALE_Y = 0.2f;
}

PlayerCar::PlayerCar()
  : forwardMovement(false)
  , backwardMovement(false)
  , leftMovement(false)
  , rightMovement(false)
  , Car(0.0f, sf::Vector2f(INITIAL_POSITION_X, INITIAL_POSITION_Y))
{
}

void PlayerCar::handleEvents(const sf::Event& event)
{
    if (event.type == sf::Event::Resized) {
        sprite.setPosition(positionPercentage.x * event.size.width, positionPercentage.y * event.size.height);
        resizeWithWindow(event.size.width, event.size.height, INITIAL_SCALE_X, INITIAL_SCALE_Y);
    }

    bool pressed = event.type != sf::Event::KeyReleased;
    forwardMovement = (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) ? pressed : forwardMovement;
    backwardMovement = (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) ? pressed : backwardMovement;
    leftMovement = (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) ? pressed : leftMovement;
    rightMovement = (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) ? pressed : rightMovement;
}

void PlayerCar::init()
{
    auto& window = WindowManager::getWindow();
    auto& texManager = TextureManager::getInstance();
    sprite.setTexture(texManager.getTexture(TextureID::CAR0));
    sprite.setScale(
        INITIAL_SCALE_X * static_cast<float>(window.getSize().x) / sprite.getTextureRect().getSize().x,
        INITIAL_SCALE_Y * static_cast<float>(window.getSize().y) / sprite.getTextureRect().getSize().y
    );
    auto spriteBounds = sprite.getLocalBounds();
    sprite.setOrigin(spriteBounds.width / 2, spriteBounds.height);
    positionPercentage = sf::Vector2f(INITIAL_POSITION_X, INITIAL_POSITION_Y);
}

void PlayerCar::update(const sf::Time& deltaTime)
{
    updateVelocity(deltaTime);
    updatePosition(deltaTime);
}

void PlayerCar::updateVelocity(const sf::Time& deltaTime)
{
    if (forwardMovement) forwardVelocity = std::min(forwardVelocity + FORWARD_INCREMENT, MAX_VELOCITY);
    if (backwardMovement) forwardVelocity = std::max(forwardVelocity - BACKWARD_DECREMENT, -MAX_VELOCITY);
    if (!forwardMovement && !backwardMovement) forwardVelocity *= (1.0f - DAMPING);
}

void PlayerCar::updatePosition(const sf::Time& deltaTime)
{
    auto windowSize = WindowManager::getWindow().getSize();

    float dt = deltaTime.asSeconds();
    float xOffset = (rightMovement ? SIDE_INCREMENT : 0) - (leftMovement ? SIDE_INCREMENT : 0);
    float speedMultiplier = static_cast<float>(windowSize.x) * SIDE_SPEED_MULTIPLIER_CONST;

    sprite.move(xOffset * speedMultiplier * dt, 0.0f);

    sf::FloatRect windowBounds(0, 0, windowSize.x, windowSize.y);
    if (intersectsBoundaries(windowBounds)) {
        float x = positionPercentage.x * windowSize.x;
        float y = positionPercentage.y * windowSize.y;
        sprite.setPosition(x, y);
    }

    positionPercentage.x = sprite.getPosition().x / windowSize.x;
    positionPercentage.y = sprite.getPosition().y / windowSize.y;
}

bool
PlayerCar::intersectsBoundaries(const sf::FloatRect& boundary)
{
    auto spriteBounds = sprite.getGlobalBounds();

    auto boundaryLeft = sf::FloatRect(0, 0, 1, boundary.getSize().y);
    auto boundaryRight =
      sf::FloatRect(boundary.getSize().x - 1, 0, 1, boundary.getSize().y);

    if (boundaryLeft.intersects(spriteBounds) ||
        boundaryRight.intersects(spriteBounds)) {
        return true;
    }
    return false;
}

void
PlayerCar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite);
}
