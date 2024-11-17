#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>
#include <memory>

class Car : public sf::Drawable {
private:
	sf::Sprite sprite;
	std::vector<sf::IntRect> animation;

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
	void calcPosition(std::shared_ptr <const sf::RenderWindow> window, const sf::Time& deltaTime);

	void restrainToBoundaries(const sf::Vector2f oldPosition, const sf::FloatRect boundary);
	void changeOrientation();

public:
	Car();

	void init(std::shared_ptr<const sf::Texture> textureAtlas);
	void handleEvents(const sf::Event& event);
	void update(std::shared_ptr <const sf::RenderWindow> window, const sf::Time& deltaTime);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // CAR_H
