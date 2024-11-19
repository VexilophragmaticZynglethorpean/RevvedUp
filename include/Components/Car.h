#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>

class Background;

class Car : public sf::Drawable
{
  private:
    enum TurnDirection
    {
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

    bool intersectsBoundaries(const sf::FloatRect& boundary);
    void turnBack(const sf::Time& deltaTime, float& angleTurned);
    void makeTurn(const sf::Time& deltaTime,
                  TurnDirection direction,
                  float& relativeAngle);

  public:
    friend class Background;
    Car();

    void init();
    void handleEvents(const sf::Event& event);
    void update(const sf::Time& deltaTime);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // CAR_H
