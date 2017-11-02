#include "ai.hpp"

#include <cstdio>
#include <cmath>

PlayerAi::PlayerAi(){
}

void PlayerAi::update(Actor *owner) {
  if ( owner->destructible && owner->destructible->isDead() ) {
    return;
  }

  int dx=0,dy=0;
  int dz=0; // non zero means z level toggle
  switch(engine.lastKey.vk) {
    case TCODK_UP : dy=-1; break;
    case TCODK_DOWN : dy=1; break;
    case TCODK_LEFT : dx=-1; break;
    case TCODK_RIGHT : dx=1; break;
    case TCODK_SPACE : dz=1; break;
    default:break;
  }

  // For special attak control
  AgileAttacker *aa = static_cast<AgileAttacker*>(owner->attacker);

  // normal move
  if (dx != 0 || dy != 0) {
    engine.gameStatus=Engine::NEW_TURN;
    moveOrAttack(owner, owner->x+dx,owner->y+dy);
  }

  // request to change z level
  if (dz == 1) {
    engine.gameStatus=Engine::NEW_TURN;
    toggleZStatus(owner);
    // attack a creature if exists in this cell
    if (owner->z->onFloor) {
      aa->setAttackMode(DROP);
      moveOrAttack(owner, owner->x+dx,owner->y+dy);
      aa->setAttackMode(PUNCH);
    }
  }

}

bool PlayerAi::moveOrAttack(Actor *owner, int targetx,int targety) {
  if ( engine.map->isWall(targetx,targety) ) return false;

  // if on the floor
  // look for living actors to attack
  if (owner->z->onFloor)
    for (Actor **iterator=engine.actors.begin();
	iterator != engine.actors.end(); iterator++) {
      Actor *actor=*iterator;
      // if player is encountered while searching actors
      if (owner == actor) continue;
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
      engine.gui->message(TCODColor::lightGrey, "There's a %s here.",actor->name);
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
  // only if player is on floor
  if (engine.player->z->onFloor)
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

void PlayerAi::toggleZStatus(Actor *owner){
  owner->z->onFloor = !owner->z->onFloor;
  engine.gui->message(TCODColor::lightGrey, owner->z->onFloor ? "You drop down." : "You disappear into the ceiling.");
  // set player color according to z level
  owner->col = owner->z->onFloor ? TCODColor::white : TCODColor::black;
}
