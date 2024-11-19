#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "Core/StateID.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <unordered_map>

class EventManager
{
  private:
    EventManager() = default;
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;

  public:
    using EventCallback = std::function<void(const sf::Event&)>;

    static EventManager& getInstance();

    void addListener(const StateID state,
                     sf::Event::EventType eventType,
                     EventCallback callback);
    void handleEvent(const StateID state, const sf::Event& event);

  private:
    std::unordered_map<
      StateID,
      std::unordered_map<sf::Event::EventType, std::vector<EventCallback>>>
      listeners;
};

#endif // EVENT_MANAGER_H
