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

void Actor::displace(int dx, int dy){
  // displace as much as possible
  if (!engine.map->canWalk(x+dx,y+dy)) {
    (dx > 0) ? dx-- : (dx < 0) ? dx++ : dx;
    (dy > 0) ? dy-- : (dy < 0) ? dy++ : dy;
  }

  x += dx;
  y += dy;
  engine.gui->message(TCODColor::white, "The %s goes flying.", name);
}
