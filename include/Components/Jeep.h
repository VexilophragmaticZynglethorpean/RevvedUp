#ifndef JEEP_H
#define JEEP_H

#include "Components/ICar.h"
#include "SFML/System/Vector2.hpp"

class Jeep : public Car, public sf::Drawable {
public:
    Jeep(sf::Vector2f spawnPoint = sf::Vector2f(0.0f, 0.0f), sf::Vector2f endPosition = sf::Vector2f(0.0f, 0.0f), sf::Vector2f fullScale = sf::Vector2f(1.0f, 1.0f));

    void init() override;
    void update(const sf::Time& deltaTime) override;

private:
    sf::Vector2f spawnPoint;
    sf::Vector2f endPosition;
    sf::Vector2f fullScale;

    sf::Vector2f lerp(const sf::Vector2f& start, const sf::Vector2f& end, float t);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

#endif // JEEP_H
