#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>

namespace {
constexpr float MAX_ROTATION = 0.005;
constexpr float ROT_ANGLE_INC = 0.001;
}

class Car : public sf::Drawable {
private:
	enum TurnDirection {
		Left = 0,
		Right = 1
	};

	sf::Sprite sprite;

	float forwardVelocity;
	float rightVelocity;

	float forwardAcceleration;
	float rightAcceleration;

	bool forwardMovement;
	bool backwardMovement;
	bool leftMovement;
	bool rightMovement;

	void calcAcceleration();
	void calcVelocity(const sf::Time& deltaTime);
	void calcPosition(const sf::Time& deltaTime);
	void calcTurn(const sf::Time& deltaTime);

	void restrainToBoundaries(const sf::Vector2f oldPosition, const sf::FloatRect boundary);
	void makeTurn(
		const sf::Time& deltaTime,
		TurnDirection direction,
		float& relativeAngle,
		const float maxRotation = MAX_ROTATION,
		const float angleIncrement = ROT_ANGLE_INC
	);

public:
	Car();

	void init();
	void handleEvents(const sf::Event& event);
	void update(const sf::Time& deltaTime);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // CAR_H
