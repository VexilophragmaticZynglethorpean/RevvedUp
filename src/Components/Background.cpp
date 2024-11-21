#include "Components/Background.h"
#include "Core/WindowManager.h"
#include "Core/TextureManager.h"

constexpr std::size_t NO_OF_ATLASES = 3;

Background::Background() : currentRow(0), currentCol(0), currentFrame(0), currentTime(0.0), atlases(3), currentTexture(TextureID::ATLAS0) {
}

void Background::init() {
    atlases.at(static_cast<std::size_t>(TextureID::ATLAS0)) = Atlas(5, 11, 55, 100.0);
    atlases.at(static_cast<std::size_t>(TextureID::ATLAS1)) = Atlas(4, 6, 23, 100.0);
    atlases.at(static_cast<std::size_t>(TextureID::ATLAS2)) = Atlas(4, 6, 23, 100.0);

    changeAtlas(currentTexture);
}

void Background::update(const sf::Time& deltaTime, const Car& car) {
    currentTime += deltaTime.asMilliseconds();

    auto& atlas = atlases.at(static_cast<std::size_t>(currentTexture));

    if (!car.forwardVelocity || !atlas.frameDurationConstant) return;
    auto frameDuration = atlas.frameDurationConstant / std::abs(car.forwardVelocity);

    if (currentTime < frameDuration) return;
    currentTime -= frameDuration;

    if (car.forwardVelocity > 0)
        incrementFrame();
    else if (car.forwardVelocity < 0)
        decrementFrame();


    sprite.setTextureRect(sf::IntRect(currentCol * atlas.tileWidth, currentRow * atlas.tileHeight, atlas.tileWidth, atlas.tileHeight));
}

void Background::handleEvents(const sf::Event& event) {
    sprite.setScale(
        static_cast<float>(event.size.width) / sprite.getTextureRect().getSize().x,
        static_cast<float>(event.size.height) / sprite.getTextureRect().getSize().y
    );
}

void Background::incrementFrame() {
    currentFrame++;
    auto& atlas = atlases.at(static_cast<std::size_t>(currentTexture));

    if(++currentCol >= atlas.cols) {
        currentCol = 0;
        currentRow++;
    }
    if (currentFrame >= atlas.frameCount) {
        currentFrame = 0;
        currentCol = 0;
        currentRow = 0;
    }
}

void Background::decrementFrame() {
    currentFrame--;
    auto& atlas = atlases.at(static_cast<std::size_t>(currentTexture));

    if(--currentCol < 0) {
        currentCol = atlas.cols-1;
        currentRow--;
    }

    if (currentFrame < 0) {
        currentFrame = atlas.frameCount-1;
        currentCol = atlas.cols-1;
        currentRow = atlas.rows-1;
    }
}

void Background::changeAtlas(TextureID textureID) {
    currentTexture = textureID;

    auto& texManager = TextureManager::getInstance();
    sprite.setTexture(texManager.getTexture(textureID));

    auto& atlas = atlases.at(static_cast<std::size_t>(currentTexture));

    if(!atlas.cols || !atlas.rows) return;

    if(!atlas.tileWidth) atlas.tileWidth = sprite.getTexture()->getSize().x / atlas.cols;
    if(!atlas.tileHeight) atlas.tileHeight = sprite.getTexture()->getSize().y / atlas.rows;

    sprite.setTextureRect(sf::IntRect(0, 0, atlas.tileWidth, atlas.tileHeight));

    auto windowSize = WindowManager::getWindow().getSize();
    sprite.setScale(
        static_cast<float>(windowSize.x) / sprite.getTextureRect().getSize().x,
        static_cast<float>(windowSize.y) / sprite.getTextureRect().getSize().y
    );
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite);
}

