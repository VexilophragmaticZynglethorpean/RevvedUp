#ifndef PLAYER_CAR_H
#define PLAYER_CAR_H

#include <SFML/Graphics.hpp>
#include "Components/ICar.h"

class PlayerCar : public Car, public sf::Drawable
{
  private:
    bool forwardMovement;
    bool backwardMovement;
    bool leftMovement;
    bool rightMovement;

    void updateVelocity(const sf::Time& deltaTime);
    void updatePosition(const sf::Time& deltaTime);

    bool intersectsBoundaries(const sf::FloatRect& boundary);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  public:
    PlayerCar();

    void init() override;
    void update(const sf::Time& deltaTime) override;
    void handleEvents(const sf::Event& event);
};

#endif // PLAYER_CAR_H
