#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <stack>
#include <memory>

#include <SFML/Graphics.hpp>
#include <Core/StateID.h>
#include <Core/State.h>

class StateManager {
private:
	std::stack<std::unique_ptr<State>> states;
	StateManager() = default;
	StateManager& operator=(const StateManager&) = delete;

public:
	static StateManager& getInstance();

	StateID getCurrentStateID() const;
	void pushState(std::shared_ptr <sf::RenderWindow> window, std::unique_ptr<State> state);
	void popState();

	void update(std::shared_ptr <const sf::RenderWindow> window, const sf::Time& deltaTime);
	void render(std::shared_ptr <sf::RenderTarget> window);
};
#endif // STATE_MANAGER_H
