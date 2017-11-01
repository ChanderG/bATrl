#include "ai.hpp"

#include <cstdio>
#include <cmath>

void PlayerAi::update(Actor *owner) {
  if ( owner->destructible && owner->destructible->isDead() ) {
    return;
  }
  int dx=0,dy=0;
  switch(engine.lastKey.vk) {
    case TCODK_UP : dy=-1; break;
    case TCODK_DOWN : dy=1; break;
    case TCODK_LEFT : dx=-1; break;
    case TCODK_RIGHT : dx=1; break;
    default:break;
  }
  if (dx != 0 || dy != 0) {
    engine.gameStatus=Engine::NEW_TURN;
    moveOrAttack(owner, owner->x+dx,owner->y+dy);
  }
}

bool PlayerAi::moveOrAttack(Actor *owner, int targetx,int targety) {
  if ( engine.map->isWall(targetx,targety) ) return false;
  // look for living actors to attack
  for (Actor **iterator=engine.actors.begin();
      iterator != engine.actors.end(); iterator++) {
    Actor *actor=*iterator;
    if ( actor->destructible && !actor->destructible->isDead()
	&& actor->x == targetx && actor->y == targety ) {
      owner->attacker->attack(owner, actor);
      return false;
    }
  }
  // look for corpses
  for (Actor **iterator=engine.actors.begin();
      iterator != engine.actors.end(); iterator++) {
    Actor *actor=*iterator;
    if ( actor->destructible && actor->destructible->isDead()
	&& actor->x == targetx && actor->y == targety ) {
      printf ("There's a %s here\n",actor->name);
    }
  }
  owner->x=targetx;
  owner->y=targety;
  return true;
}

void MonsterAi::update(Actor *owner) {
  if ( owner->destructible && owner->destructible->isDead() ) {
    return;
  }
  // directly attack player wherever he is in the map
  moveOrAttack(owner, engine.player->x,engine.player->y);
}

void MonsterAi::moveOrAttack(Actor *owner, int targetx, int targety) {
  int dx = targetx - owner->x;
  int dy = targety - owner->y;
  float distance=sqrtf(dx*dx+dy*dy);
  if ( distance >= 2 ) {
    dx = (int)(round(dx/distance));
    dy = (int)(round(dy/distance));
    if ( engine.map->canWalk(owner->x+dx,owner->y+dy) ) {
      owner->x += dx;
      owner->y += dy;
    }
  } else if ( owner->attacker ) {
    owner->attacker->attack(owner,engine.player);
  }
}

