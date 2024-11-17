#include <Core/StateManager.h>

StateManager& StateManager::getInstance() {
        static StateManager instance;
        return instance;
}

StateID StateManager::getCurrentStateID() const {
        if(states.empty()) return StateID::Default;
        return states.top()->getID();
}

void StateManager::pushState(std::shared_ptr <sf::RenderWindow> window, std::unique_ptr<State> state) {
        if(state == nullptr) return;
        states.push(std::move(state));
        states.top()->init(window);
}

void StateManager::popState() {
        if (!states.empty()) {
                states.top()->exit();
                states.pop();
        }
}

void StateManager::update(std::shared_ptr <const sf::RenderWindow> window, const sf::Time& deltaTime) {
        if (!states.empty()) {
                states.top()->update(window, deltaTime);
        }
}

void StateManager::render(std::shared_ptr <sf::RenderTarget> window) {
        if (!states.empty()) {
                states.top()->render(window);
        }
}
