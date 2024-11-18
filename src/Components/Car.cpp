#include <Components/Car.h>
#include <Core/Global.h>

#include <algorithm>
#include <future>
#include <iostream>

#ifdef DEV_PHASE
#include <imgui.h>
#include <imgui-SFML.h>
#endif

constexpr float FORWARD_INCREMENT = 0.1f;
constexpr float BACKWARD_DECREMENT = 0.1f;
constexpr float RIGHT_INCREMENT = 0.1f;
constexpr float LEFT_DECREMENT = 0.1f;

constexpr float DAMPING = 0.1f;
constexpr float MAX_DAMPING = 1.0f;
constexpr float MAX_X_ACCELERATION = 10.0f;
constexpr float MAX_Y_ACCELERATION = 10.0f;


Car::Car() : 
	forwardVelocity(0.0f),
	rightVelocity(0.0f),

	forwardAcceleration(0.0f),
	rightAcceleration(0.0f),

	forwardMovement(false),
	backwardMovement(false),
	leftMovement(false),
	rightMovement(false)
{}

void Car::handleEvents(const sf::Event& event) {
        bool pressed = event.type != sf::Event::KeyReleased;
        bool W_Up = event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up;
        bool A_Left = event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left;
        bool S_Down = event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down;
        bool D_Right = event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right;

        forwardMovement = false;
        /*forwardMovement = W_Up ? pressed : forwardMovement;*/
        leftMovement = A_Left ? pressed : leftMovement;
        backwardMovement = S_Down ? pressed : backwardMovement;
        rightMovement = D_Right ? pressed : rightMovement;
}

void Car::init() {
        auto rect = sf::IntRect(565, 39, 148, 206);

        sprite.setPosition(500, 500);

        sprite.setTexture(Global::getTexture());
        sprite.setTextureRect(rect);

        auto spriteBounds = sprite.getLocalBounds();
        sprite.setOrigin(spriteBounds.width/2, spriteBounds.height);
}

void Car::update(const sf::Time& deltaTime) {
        calcPosition(deltaTime);
        calcTurn(deltaTime);

        #ifdef DEV_PHASE
        ImGui::Begin("Debug");
        static float angle = 0.0f;
        ImGui::DragFloat("Angle", &angle);
        sprite.setRotation(angle);
        ImGui::End();
        #endif
}

void Car::calcAcceleration() {
        if (forwardMovement) forwardAcceleration += FORWARD_INCREMENT;
        if (backwardMovement) forwardAcceleration -= BACKWARD_DECREMENT;
        if (!forwardMovement && !backwardMovement) forwardAcceleration = 0.0f;

        forwardAcceleration = std::clamp(forwardAcceleration, -MAX_X_ACCELERATION, MAX_X_ACCELERATION);

        if (rightMovement) rightAcceleration += RIGHT_INCREMENT;
        if (leftMovement) rightAcceleration -= LEFT_DECREMENT;
        if (!rightMovement && !leftMovement) rightAcceleration = 0.0f;

        rightAcceleration = std::clamp(rightAcceleration, -MAX_Y_ACCELERATION, MAX_Y_ACCELERATION);
}

void Car::calcVelocity(const sf::Time& deltaTime) {
        calcAcceleration();

        float dt = deltaTime.asSeconds();

        forwardVelocity += forwardAcceleration ?
                                forwardAcceleration * dt :
                                - forwardVelocity * std::min(MAX_DAMPING, DAMPING * dt);

        rightVelocity = rightAcceleration ?
                                rightVelocity + rightAcceleration * dt :
                                0.0f;
}

void Car::calcPosition(const sf::Time& deltaTime) {
        calcVelocity(deltaTime);

        float dt = deltaTime.asSeconds();

        float yOffset = forwardVelocity * dt;
        float xOffset = rightVelocity * dt;

        auto windowSize = Global::getWindow().getSize();

        sf::Vector2f spriteOldPosition = sprite.getPosition();
        sf::FloatRect windowBounds(0, 0, windowSize.x, windowSize.y);

        sprite.move(xOffset, -yOffset);
        
        restrainToBoundaries(spriteOldPosition, windowBounds);
}

void Car::restrainToBoundaries(const sf::Vector2f oldPosition, const sf::FloatRect boundary) {
        auto spriteBounds = sprite.getGlobalBounds();

        auto boundaryLeft = sf::FloatRect(0, 0, 1, boundary.getSize().y);
        auto boundaryRight = sf::FloatRect(boundary.getSize().x-1, 0, 1, boundary.getSize().y);
        auto boundaryTop = sf::FloatRect(0, 0, boundary.getSize().x, 1);
        auto boundaryBottom = sf::FloatRect(0, boundary.getSize().y-1, boundary.getSize().x, boundary.getSize().y);

        if (
                boundaryLeft.intersects(spriteBounds) ||
                boundaryRight.intersects(spriteBounds) ||
                boundaryTop.intersects(spriteBounds) ||
                boundaryBottom.intersects(spriteBounds)
        ) {
                sprite.setPosition(oldPosition);
        }
}



void Car::makeTurn(
        const sf::Time& deltaTime,
        TurnDirection direction,
        float& relativeAngle,
        const float maxRotation,
        const float angleIncrement
) {
        int sign = direction ? -1 : 1;
        if (sign * relativeAngle > maxRotation) return;

        sprite.rotate(relativeAngle);
        relativeAngle += sign * angleIncrement * deltaTime.asSeconds();
}

void Car::calcTurn(const sf::Time& deltaTime) {
        static float angleTurned = 0.0f;
        static float turnBack = 0.0f;

        if (leftMovement && rightVelocity < 0.0f) {
                makeTurn(deltaTime, Left, angleTurned);
        } else if (rightMovement && rightVelocity > 0.0f) {
                makeTurn(deltaTime, Right, angleTurned);
        } else {
                if (angleTurned > 0) {
                        makeTurn(deltaTime, Left, turnBack, angleTurned);
                } else if (angleTurned < 0) {
                        makeTurn(deltaTime, Right, turnBack, angleTurned);
                } else {
                        turnBack = 0.0f;
                }
        }
}

void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(sprite);
}
