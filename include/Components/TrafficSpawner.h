#ifndef TRAFFIC_SPAWNER_H
#define TRAFFIC_SPAWNER_H

#include "Components/Jeep.h"
#include <deque>
#include <mutex>

class TrafficSpawner {
public:
    TrafficSpawner(float leftBound, float rightBound, float upperBoundY, float forwardVelocity, sf::Vector2f fullScale, float spawnInterval);
    
    void update(const sf::Time& deltaTime);
    void updateTraffic(const sf::Time& deltaTime); 
    std::deque<Jeep>& getTraffic();

private:
    void spawnTraffic();
    void removeOutOfScreenTraffic();

    float leftBound;
    float rightBound;
    float upperBoundY;
    float forwardVelocity;
    sf::Vector2f fullScale;

    std::deque<Jeep> traffic;
    std::mutex trafficMutex;

    float spawnInterval;
    float elapsedTime;
};

#endif // TRAFFIC_SPAWNER_H
