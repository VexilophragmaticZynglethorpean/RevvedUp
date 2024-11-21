#ifndef JEEP_H
#define JEEP_H

#include "Components/ICar.h"
#include "SFML/System/Vector2.hpp"

class Jeep : public Car, public sf::Drawable {
public:
    Jeep();

    void init() override;
    void update(const sf::Time& deltaTime) override;

private:
    sf::Vector2f spawnRangeLeft;
    sf::Vector2f spawnRangeRight;

    float fullScale;

    sf::Vector2f lerp(const sf::Vector2f& start, const sf::Vector2f& end, float t);
    void updatePosition(const sf::Time& deltaTime);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

#endif // JEEP_H
