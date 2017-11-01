#ifndef ACTOR_H
#define ACTOR_H

#include "attacker.hpp"
#include "destructible.hpp"
#include "ai.hpp"
#include "z.hpp"
#include "libtcod.hpp"

class Attacker;
class Destructible;
class Ai;
class Z;

class Actor {
  public:
    int x,y; // position
    int ch;  // code repn the actor
    TCODColor col; // col of character
    const char* name;
    bool blocks;
    Attacker *attacker; // something that deals damage
    Destructible *destructible; // something that can be damaged
    Ai *ai; // something self-updating
    Z *z; // accessing z levels

    Actor(int x, int y, int ch, const char* name, const TCODColor &col);
    void render() const;
    void update();
};

#endif
