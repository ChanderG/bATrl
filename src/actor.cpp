#include "actor.hpp"
#include "libtcod.hpp"
#include "engine.hpp"

#include "cstdio"
#include "cmath"

Actor::Actor(int x, int y, int ch, const char* name, const TCODColor &col ): x(x), y(y), ch(ch), col(col), name(name), blocks(true), attacker(NULL), destructible(NULL), ai(NULL), z(NULL){
}

void Actor::render() const {
  // player has full sense upto this distance
  //if (sqrt((x-engine.player->x)*(x-engine.player->x) + (y-engine.player->y)*(y-engine.player->y)) < 10){
  // normal render
  TCODConsole::root->setChar(x, y, ch);
  TCODConsole::root->setCharForeground(x,y,col);
  //}
}

void Actor::update(){
  if (ai) ai->update(this);
}

/*
 * Displace dx, dy
 *
 * CASE 1: Full possible, simply displace the actor.
 * CASE 2: Vector interrupted by some object:
 *        2A: Non movable (walls, other large objects): absorb some energy (ie cause damage
 *            to the actor and reflect/bounce off the wall or stick to it based on coeff of
 *            restitution.
 *        2B: Movable / small objects (including other actors): cause damage to the actor
 *            and transfer an impulse to the other actor.
 */
void Actor::displace(int dx, int dy){
  // first calculate how much of the full vector is possible
  int tx=0, ty=0;
  int ix=0, iy=0;
  // calc smallest possible displacement
  tx = (tx > dx) ? tx-1 : ((tx < dx) ? tx+1 : tx);
  ty = (ty > dy) ? ty-1 : ((ty < dy) ? ty+1 : ty);

  // try out till you reach full disp
  while(!((ix == dx) && (iy == dy))){
    // check if curr displacement is OK
    if (!engine.map->canWalk(x+tx, y+ty)){
      // cant walk here;
      break;
    }
    // store current disp
    ix = tx;
    iy = ty;
    // try to displace more
    tx = (tx > dx) ? tx-1 : ((tx < dx) ? tx+1 : tx);
    ty = (ty > dy) ? ty-1 : ((ty < dy) ? ty+1 : ty);
  }

  // ix,iy is perfectly OK
  // tx,ty is where another object/wall stands stopping us from going forward

  // full displacement is possible
  if((ix == dx) && (iy == dy)){
    // fully displace ourselves
    x+=ix; y+=iy;
    engine.gui->message(TCODColor::white, "The %s goes flying.", name);
    return;
  }

  // TODO: deal with ix,iy == 0,0 case

  // if there is a wall at target
  // TODO: have to bounce the thug off the wall by reversing the vector correctly
  if (engine.map->isWall(x+tx,y+ty)){
    // maximal displace
    x+=ix; y+=iy;
    // for now simply damage the actor
    destructible->takeDamage(this, destructible->defense + 5);
    engine.gui->message(TCODColor::white, "%s smashes against the wall and sustains 5 damage.", name);
    return;
  }


  // if there is another actor at tx,ty
  // damage us and displace the other actor too
  for (Actor **iterator=engine.actors.begin();
      iterator != engine.actors.end(); iterator++) {
    Actor *actor=*iterator;
    // if player is encountered while searching actors
    // don't do anything
    if (engine.player == actor) continue;
    if ( actor->destructible && !actor->destructible->isDead()
	&& actor->x == x+tx && actor->y == y+ty ) {
      // damage ourselves and displace this actor
      destructible->takeDamage(this, destructible->defense + 3);
      engine.gui->message(TCODColor::white, "The %s crashes into a %s and sustains 3 damage.", name, actor->name);
      // transfer half of the impulse to the other actor
      actor->displace(dx/2, dy/2);
      // check if the other actor has freed up the location
      if (engine.map->canWalk(x+tx, y+ty)){
	// if so, go there
	x+=tx; y+=ty;
      } else {
	// else go as far as possible
	x+=ix; y+=iy;
      }
      return;
    }
  }
}
