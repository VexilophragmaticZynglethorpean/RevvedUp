#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <memory>
#include <stack>
#include "Core/State.h"
#include "Core/StateID.h"
#include <SFML/Graphics.hpp>

class StateManager
{
  private:
    std::stack<std::unique_ptr<State>> states;
    StateManager() = default;

  public:
    static StateManager& getInstance();

    StateID getCurrentStateID() const;
    void pushState(std::unique_ptr<State> state);
    void popState();

    void update(const sf::Time& deltaTime);
    void render();

    StateManager& operator=(const StateManager&) = delete;
    StateManager(const StateManager&) = delete;
};
#endif // STATE_MANAGER_H
