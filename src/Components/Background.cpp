#include "Core/TextureManager.h"
#include "Components/Background.h"
#include "Core/Global.h"
#include "SFML/Graphics/Rect.hpp"

Background::Background(std::size_t rows, std::size_t cols, std::size_t frameCount) : rows(rows), cols(cols), frameCount(frameCount), currentRow(1), currentCol(1), currentFrame(0), currentTime(0.0) {
}

void Background::init() {
    auto texture = TextureManager::getInstance().getTexture(TextureManager::ATLAS0);

    sprite.setTexture(texture);

    tileSize.x = texture.getSize().x / cols;
    tileSize.y = texture.getSize().y / rows;
    sprite.setTextureRect(sf::IntRect(0, 0, tileSize.x, tileSize.y));

}

void Background::update(const sf::Time& deltaTime, const Car& car) {
    currentTime += deltaTime.asMilliseconds();
    constexpr float SPED = 1.0f;

    if (!car.forwardVelocity) return;

    auto frameDuration = 1.0f / std::abs(car.forwardVelocity);
    if (currentTime < frameDuration) return;

    currentTime -= frameDuration;

    if (car.forwardVelocity > 0)
        incrementFrame();
    else if (car.forwardVelocity < 0)
        decrementFrame();

    auto windowSize = Global::getWindow().getSize();
    sprite.setScale(
        static_cast<float>(windowSize.x) / texture.getSize().x,
        static_cast<float>(windowSize.y) / texture.getSize().y
    );
}

void Background::incrementFrame() {
    currentFrame++;

    if(++currentRow > rows) {
        --currentRow;

        if (++currentCol > cols) {
            currentRow = 1;
            currentCol = 1;
        }
    }

    int left = 0 + (currentRow-1) * tileSize.x;
    int top = 0 + (currentCol-1) * tileSize.y;
    int width = tileSize.x;
    int height = tileSize.y;

    sprite.setTextureRect(sf::IntRect(left, top, width, height));
}

void Background::decrementFrame() {
    currentFrame--;

    if(--currentRow < 0) {
        ++currentRow;

        if (--currentCol > cols) {
            currentRow = rows;
            currentCol = cols;
        }
    }

    int left = 0 + (currentRow-1) * tileSize.x;
    int top = 0 + (currentCol-1) * tileSize.y;
    int width = tileSize.x;
    int height = tileSize.y;

    sprite.setTextureRect(sf::IntRect(left, top, width, height));
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite);
}

