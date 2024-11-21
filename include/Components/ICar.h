#ifndef CAR_H
#define CAR_H

#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>

class Car
{
  protected:

    sf::Sprite sprite;
    float forwardVelocity;

    sf::Vector2f positionPercentage;

  public:
    explicit Car(float forwardVelocity, sf::Vector2f positionPercentage) : forwardVelocity(forwardVelocity), positionPercentage(positionPercentage) {}
    virtual ~Car() = default;

    virtual void init() = 0;
    virtual void update(const sf::Time& deltaTime) = 0;

    float getForwardVelocity() const {
        return forwardVelocity;
    }

sf::Vector2f getPositionPercentage() const {
        return positionPercentage;
}
};

#endif // CAR_H

