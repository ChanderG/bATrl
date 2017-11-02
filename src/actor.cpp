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
  // store init locations
  int ox=dx, oy=dy;
  // displace as much as possible
  while (!engine.map->canWalk(x+dx,y+dy)) {
    dx = (dx > 0) ? dx-1 : ((dx < 0) ? dx+1 : dx);
    dy = (dy > 0) ? dy-1 : ((dy < 0) ? dy+1 : dy);
    if(dx == 0 && dy == 0) break;
  }

  if(dx == 0 && dy == 0) {
    // wall behind the actor
    // bounce the actor against the wall
    dx = (ox > 0) ? -1 : (ox < 0) ? +1 : 0;
    dy = (oy > 0) ? -1 : (oy < 0) ? +1 : 0;
    // sustain more damage -> due to hitting the wall
    destructible->takeDamage(this, destructible->defense + 5);
    engine.gui->message(TCODColor::white, "%s bounces against the wall and sustains 5 damage.");
  }

  x += dx;
  y += dy;
  engine.gui->message(TCODColor::white, "The %s goes flying.", name);
}
