#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>


    enum class TurnDirection
    {
        Left = 0,
        Right = 1
    };

class Background;
class Car : public sf::Drawable
{
  private:

    sf::Sprite sprite;

    float forwardVelocity;
    float forwardAcceleration;

    sf::Vector2f positionPercentage;

    bool forwardMovement;
    bool backwardMovement;
    bool leftMovement;
    bool rightMovement;

    void calcAcceleration();
    void calcVelocity(const sf::Time& deltaTime);
    void calcPosition(const sf::Time& deltaTime);
    void calcTurn(const sf::Time& deltaTime);

    bool intersectsBoundaries(const sf::FloatRect& boundary);

  public:
    friend class Background;
    Car();

    void init();
    void handleEvents(const sf::Event& event);
    void update(const sf::Time& deltaTime);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // CAR_H
