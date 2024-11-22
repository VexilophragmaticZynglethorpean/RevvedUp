#ifndef CAR_H
#define CAR_H

#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>

class Car
{
  protected:

    float forwardVelocity;

    sf::Vector2f positionPercentage;

  public:
    sf::Sprite sprite;
    explicit Car(float forwardVelocity, sf::Vector2f positionPercentage) : forwardVelocity(forwardVelocity), positionPercentage(positionPercentage) {}
    virtual ~Car() = default;

    virtual void init() = 0;
    virtual void update(const sf::Time& deltaTime) = 0;

void resizeWithWindow(float newWindowWidth, float newWindowHeight, float initialScaleX, float initialScaleY) {
        sprite.setScale(
            initialScaleX * static_cast<float>(newWindowWidth) / sprite.getTextureRect().getSize().x,
            initialScaleY * static_cast<float>(newWindowHeight) / sprite.getTextureRect().getSize().y
        );
}


    float getForwardVelocity() const {
        return forwardVelocity;
    }

sf::Vector2f getPositionPercentage() const {
        return positionPercentage;
}
};

#endif // CAR_H

