#include "Core/StateManager.h"

StateManager&
StateManager::getInstance()
{
    static StateManager instance;
    return instance;
}

StateID
StateManager::getCurrentStateID() const
{
    if (states.empty())
        return StateID::Default;
    return states.top()->getID();
}

void
StateManager::pushState(std::unique_ptr<State> state)
{
    if (state == nullptr)
        return;
    states.push(std::move(state));
    states.top()->init();
}

void
StateManager::popState()
{
    if (!states.empty()) {
        states.top()->exit();
        states.pop();
    }
}

void
StateManager::update(const sf::Time& deltaTime)
{
    if (!states.empty()) {
        states.top()->update(deltaTime);
    }
}

void
StateManager::render()
{
    if (!states.empty()) {
        states.top()->render();
    }
}
