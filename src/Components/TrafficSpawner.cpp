#include "Components/TrafficSpawner.h"
#include <random>
#include <iostream>

TrafficSpawner::TrafficSpawner(float leftBound, float rightBound, float upperBoundY, float forwardVelocity, sf::Vector2f fullScale, float spawnInterval)
    : leftBound(leftBound),
      rightBound(rightBound),
      upperBoundY(upperBoundY),
      forwardVelocity(forwardVelocity),
      fullScale(fullScale),
      spawnInterval(spawnInterval),
      elapsedTime(0.0f)
{
}

void TrafficSpawner::removeOutOfScreenTraffic() {
    while (!traffic.empty() && traffic.front().getPosition().y > 1.0f) {
        traffic.pop_front();
    }
}

void TrafficSpawner::update(const sf::Time& deltaTime) {
    elapsedTime += deltaTime.asSeconds();

    removeOutOfScreenTraffic();

    for (auto& jeep : traffic) {
        jeep.update(deltaTime);
    }

    if (elapsedTime >= spawnInterval) {
        spawnTraffic();
        elapsedTime = 0.0f;
    }
}

void TrafficSpawner::spawnTraffic() {
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_real_distribution<float> xDistr(leftBound, rightBound);

    float spawnX = xDistr(eng);
    float spawnY = upperBoundY;

    if (leftBound == rightBound) return;
    float endPositionX = (spawnX - leftBound) / (rightBound - leftBound);

    std::clog << leftBound << ", " << rightBound << ", " << endPositionX << std::endl;
    std::clog << spawnX << ", " << spawnY << ", " << endPositionX << std::endl;

    /*Jeep newJeep(sf::Vector2f(spawnX, spawnY), sf::Vector2f(endPositionX, 1.0f), forwardVelocity, fullScale);*/
    Jeep newJeep(sf::Vector2f(0.53, 0.56), sf::Vector2f(0.5f, 1.5f), 5.0f, sf::Vector2f(2.5f, 2.5f));
    newJeep.init();

    traffic.push_back(std::move(newJeep));
}

void TrafficSpawner::draw(sf::RenderTarget& target){
    for (auto& jeep : traffic) {
        target.draw(jeep);
    }
}

