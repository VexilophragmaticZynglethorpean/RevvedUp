#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
#include <Core/StateID.h>

class State {
protected:
	StateID id;
public:
	virtual ~State() = default;

	StateID getID() const {
		return id;
	}
	
	virtual void init() = 0;
	virtual void update(const sf::Time& deltaTime) = 0;
	virtual void render() = 0;
	
	virtual void exit() = 0;
};

#endif // STATE_H
