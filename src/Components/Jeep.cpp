#include "Components/Jeep.h"
#include "Core/WindowManager.h"

sf::Vector2f Jeep::lerp(const sf::Vector2f& start, const sf::Vector2f& end, float t) {
    return start + t * (end - start);
}

void Jeep::updatePosition(const sf::Time& deltaTime) {
    auto dt = LERP_SPEED * deltaTime.asSeconds();
    auto currentPosition = sprite.getPosition();

    auto windowSize = WindowManager::getWindow().getSize();
   sf::Vector2f endPosition;

    endPosition.x = windowSize.x * (spawnPoint.x - spawnRangeMid) / (spawnRangeLeft.x - spawnRangeRight.x);
    endPosition.y = windowSize.y + FULL_SCALE * sprite.getGlobalBounds().height;
    sprite.setPosition(currentPosition, )
}

void Jeep::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite);
}
