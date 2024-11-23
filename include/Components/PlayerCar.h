#ifndef PLAYER_CAR_H
#define PLAYER_CAR_H

#include <SFML/Graphics.hpp>

class PlayerCar
  : public sf::Drawable
{
  private:
    bool forwardMovement;
    bool backwardMovement;
    bool leftMovement;
    bool rightMovement;

  sf::Sprite sprite;
    float forwardVelocity;
    sf::Vector2f positionPercentage;

    void updateVelocity(const sf::Time& deltaTime);
    void updatePosition(const sf::Time& deltaTime);

    bool intersectsBoundaries(const sf::FloatRect& boundary);

    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override;

    void resizeWithWindow(float newWindowWidth,
                          float newWindowHeight,
                          float initialScaleX,
                          float initialScaleY);

  public:
    PlayerCar();

    void init();
    void update(const sf::Time& deltaTime);
    void handleEvents(const sf::Event& event);

    float getForwardVelocity() const;
    sf::Vector2f getPositionPercentage() const;
    float getWidthPercentage() const;
    void setVelocity(float velocity);
};

#endif // PLAYER_CAR_H
