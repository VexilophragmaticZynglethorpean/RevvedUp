#include "Components/Jeep.h"

sf::Vector2f Jeep::lerp(const sf::Vector2f& start, const sf::Vector2f& end, float t) {
    return start + t * (end - start);
}
