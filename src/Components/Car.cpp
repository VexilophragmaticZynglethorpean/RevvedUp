#include <Components/Car.h>
#include <algorithm>

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

enum CarOrientation {
        TOP_LEFT,
        TOP,
        TOP_RIGHT
};
constexpr size_t NO_OF_ORIENTATIONS = 3;


Car::Car() : 
        animation(NO_OF_ORIENTATIONS),

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

        forwardMovement = W_Up ? pressed : forwardMovement;
        leftMovement = A_Left ? pressed : leftMovement;
        backwardMovement = S_Down ? pressed : backwardMovement;
        rightMovement = D_Right ? pressed : rightMovement;
}

void Car::init(std::shared_ptr<const sf::Texture> textureAtlas) {
        animation[TOP_LEFT] = sf::IntRect(263, 59, 242, 174);
        animation[TOP] = sf::IntRect(565, 39, 148, 206);
        animation[TOP_RIGHT] = sf::IntRect(773, 53, 252, 184);

        sprite.setPosition(500, 500);

        sprite.setTexture(*textureAtlas);
        sprite.setTextureRect(animation[TOP]);

        auto spriteBounds = sprite.getLocalBounds();
        sprite.setOrigin(spriteBounds.width/2, spriteBounds.height);
}

void Car::update(std::shared_ptr <const sf::RenderWindow> window, const sf::Time& deltaTime) {
        calcPosition(window, deltaTime);
}

void Car::calcAcceleration() {
        if (forwardMovement) forwardAcceleration += FORWARD_INCREMENT;
        if (backwardMovement) forwardAcceleration -= BACKWARD_DECREMENT;
        if (!forwardMovement && !backwardMovement) forwardAcceleration = 0.0f;

        forwardAcceleration = std::min(forwardAcceleration, MAX_X_ACCELERATION);
        forwardAcceleration = std::max(forwardAcceleration, -MAX_X_ACCELERATION);

        if (rightMovement) rightAcceleration += RIGHT_INCREMENT;
        if (leftMovement) rightAcceleration -= LEFT_DECREMENT;
        if (!rightMovement && !leftMovement) rightAcceleration = 0.0f;

        rightAcceleration = std::min(rightAcceleration, MAX_Y_ACCELERATION);
        rightAcceleration = std::max(rightAcceleration, -MAX_Y_ACCELERATION);
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

void Car::calcPosition(std::shared_ptr <const sf::RenderWindow> window, const sf::Time& deltaTime) {
        calcVelocity(deltaTime);

        float dt = deltaTime.asSeconds();

        float yOffset = forwardVelocity * dt;
        float xOffset = rightVelocity * dt;

        sf::Vector2f spriteOldPosition = sprite.getPosition();
        sf::FloatRect windowBounds(0, 0, window->getSize().x, window->getSize().y);

        sprite.move(xOffset, -yOffset);
        
        changeOrientation();
        restrainToBoundaries(spriteOldPosition, windowBounds);
}

void Car::restrainToBoundaries(const sf::Vector2f oldPosition, const sf::FloatRect boundary) {
        auto spriteBounds = sprite.getGlobalBounds();

        bool moved_left_out_of_boundary = spriteBounds.left < boundary.left;
        bool moved_right_out_of_boundary = spriteBounds.left + spriteBounds.width > boundary.left + boundary.width;

        bool moved_top_out_of_boundary = spriteBounds.top < boundary.top;
        bool moved_bottom_out_of_boundary = spriteBounds.top + spriteBounds.height > boundary.top + boundary.height;

        if (moved_top_out_of_boundary) {
                sprite.setPosition(oldPosition.x, spriteBounds.height);
        }

        if (moved_bottom_out_of_boundary) {
                sprite.setPosition(oldPosition.x, boundary.height);
                forwardVelocity = 0;
                forwardAcceleration = 0;
        }

        if (moved_left_out_of_boundary) {
                sprite.setPosition(spriteBounds.width/2, oldPosition.y);
        }

        if (moved_right_out_of_boundary) {
                sprite.setPosition(boundary.width - spriteBounds.width/2, oldPosition.y);
        }
}

void Car::changeOrientation() {
        sf::IntRect textureRect;
        textureRect = animation[TOP];

        if (rightMovement)
                textureRect = animation[TOP_RIGHT];
        if (leftMovement)
                textureRect = animation[TOP_LEFT];

        sprite.setTextureRect(textureRect);
}

void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        #ifdef DEV_PHASE
        ImGui::Begin("Debug");
        float angle;
        ImGui::DragFloat("Angle", &angle);
        /*sprite.rotate(angle);*/
        ImGui::End();
        #endif

        target.draw(sprite);
}
