#include "actor.hpp"
#include "libtcod.hpp"
#include "engine.hpp"

#include "cstdio"

Actor::Actor(int x, int y, int ch, const char* name, const TCODColor &col ): x(x), y(y), ch(ch), col(col), name(name), blocks(true), attacker(NULL), destructible(NULL), ai(NULL), z(NULL){
}

void Actor::render() const {
  TCODConsole::root->setChar(x, y, ch);
  TCODConsole::root->setCharForeground(x,y,col);
}

void Actor::update(){
  if (ai) ai->update(this);
}
