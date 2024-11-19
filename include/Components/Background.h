#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>
#include <Components/Car.h>

class Background 
  : public sf::Drawable
{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2i tileSize;
    std::size_t frameCount;

    double currentTime;
    std::size_t currentFrame;
    std::size_t currentRow, currentCol;
    std::size_t rows, cols;

    void incrementFrame();
    void decrementFrame();

public:
    void init ();
    void update(const sf::Time& deltaTime, const Car& car);

    Background(std::size_t rows, std::size_t cols, std::size_t frameCount);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // BACKGROUND_H

