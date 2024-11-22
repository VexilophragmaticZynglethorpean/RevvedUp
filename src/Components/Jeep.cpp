#include "Components/Jeep.h"
#include "Core/TextureManager.h"
#include <random>

constexpr float LERP_SPEED = 0.5f;

Jeep::Jeep(sf::Vector2f spawnPoint, sf::Vector2f endPosition, sf::Vector2f fullScale) : spawnPoint(spawnPoint), endPosition(endPosition),  Car(10.0f, sf::Vector2f(0.0f, 0.0f)) {
}

sf::Vector2f Jeep::lerp(const sf::Vector2f& start, const sf::Vector2f& end, float t) {
    return start + t * (end - start);
}

void Jeep::init() {
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, 1);

    auto& tex = TextureManager::getInstance().getTexture(TextureID::JEEP);
    sprite.setTexture(tex);

    sf::IntRect rect;
    rect.left = distr(eng) * tex.getSize().x / 2;
    rect.top = 0;
    rect.width = tex.getSize().y;
    rect.height = tex.getSize().y;

    sprite.setTextureRect(rect);
    sprite.setScale(0.0f, 0.0f);
}

void Jeep::update(const sf::Time& deltaTime) {
    auto dt = LERP_SPEED * deltaTime.asSeconds();
    auto currentPosition = sprite.getPosition();
    auto currentScale = sprite.getScale();

    sprite.setPosition(lerp(currentPosition, endPosition, dt));
    sprite.setScale(lerp(currentScale, fullScale, dt));
}

void Jeep::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite);
}
