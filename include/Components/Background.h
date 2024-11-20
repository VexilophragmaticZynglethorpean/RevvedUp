#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>
#include "Components/Car.h"
#include "Core/TextureManager.h"

class Background 
  : public sf::Drawable
{
private:
    struct Atlas {
        std::size_t tileWidth, tileHeight;
        std::size_t rows, cols;
        std::size_t frameCount;

        Atlas(std::size_t cols = 0, std::size_t rows = 0, std::size_t frameCount = 0)
        : cols(cols), rows(rows), frameCount(frameCount), tileWidth(0), tileHeight(0) {}
    };

    sf::Sprite sprite;
    TextureManager::TextureID currentTexture;
    std::vector<Atlas> atlases;

    double currentTime;
    int currentFrame;
    int currentRow, currentCol;

    void incrementFrame();
    void decrementFrame();

public:
    void init();
    void update(const sf::Time& deltaTime, const Car& car);
    void handleEvents(const sf::Event& event);

    void changeAtlas(TextureManager::TextureID id);

    Background();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // BACKGROUND_H
