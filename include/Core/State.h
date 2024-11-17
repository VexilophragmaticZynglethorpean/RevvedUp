#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
#include <Core/StateID.h>
#include <memory>

class State {
protected:
	StateID id;
public:
	virtual ~State() = default;

	StateID getID() const {
		return id;
	}
	
	virtual void init(std::shared_ptr <sf::RenderWindow> window) = 0;
	virtual void update(std::shared_ptr <const sf::RenderWindow> window, const sf::Time& deltaTime) = 0;
	virtual void render(std::shared_ptr <sf::RenderTarget> window) = 0;
	
	virtual void exit() = 0;
};

#endif // STATE_H
