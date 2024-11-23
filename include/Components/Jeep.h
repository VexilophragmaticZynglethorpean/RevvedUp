/*#ifndef JEEP_H*/
/*#define JEEP_H*/
/**/
/*#include "Components/ICar.h"*/
/**/
/*class Jeep*/
/*  : public Car*/
/*  , public sf::Drawable*/
/*{*/
/*  public:*/
/*    Jeep(sf::Vector2f spawnPoint,*/
/*         sf::Vector2f endPosition,*/
/*         float forwardVelocity,*/
/*         sf::Vector2f fullScale);*/
/**/
/*    void init() override;*/
/*    void update(const sf::Time& deltaTime) override;*/
/*    sf::Vector2f getPosition() const;*/
/**/
/*  private:*/
/*    sf::Vector2f endPosition;*/
/*    sf::Vector2f fullScale;*/
/*    float dt;*/
/**/
/*    sf::Vector2f lerp(const sf::Vector2f& start,*/
/*                      const sf::Vector2f& end,*/
/*                      float t);*/
/*    float lerp(float start, float end, float t);*/
/*    float terp(float start, float end, float t);*/
/*    virtual void draw(sf::RenderTarget& target,*/
/*                      sf::RenderStates states) const override;*/
/*};*/
/**/
/*#endif // JEEP_H*/
