#ifndef STATE_H
#define STATE_H

#include "Core/StateID.h"
#include <SFML/Graphics.hpp>

class State
{
  protected:
    StateID id;

  public:
    virtual ~State() = default;

    StateID getID() const { return id; }

    virtual void init() = 0;
    virtual void update(const sf::Time& deltaTime) = 0;
    virtual void render() = 0;

    virtual void exit() = 0;
};

#endif // STATE_H
