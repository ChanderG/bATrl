#include "ai.hpp"

#include <cstdio>

#define PLAYER_HEAL_ODDS 3 // odds of healing this turn
#define PLAYER_HEAL_AMT 2  // amount healed

PlayerAi::PlayerAi(){
}

void PlayerAi::update(Actor *owner) {
  if ( owner->destructible && owner->destructible->isDead() ) {
    return;
  }

  int dx=0,dy=0;
  int dz=0; // non zero means z level toggle
  bool c=false; // pressed a character key
  switch(engine.lastKey.vk) {
    case TCODK_UP : dy=-1; break;
    case TCODK_DOWN : dy=1; break;
    case TCODK_LEFT : dx=-1; break;
    case TCODK_RIGHT : dx=1; break;
    case TCODK_SPACE : dz=1; break;
    case TCODK_CHAR: c=true; break;

    default:break;
  }

  // handle char keys
  AgileAttack mode = NONE;
  if (c == true){
    switch(engine.lastKey.c){
      case 'k': mode=KICK; break;
      case 'b': mode=BACKHAND; break;
      case 'p': mode=POUND; break;
      case 'j': mode=JUMP; break;
      case 'l': mode=LAUNCH; break;
      default:break;
    }
  }

  // For special attack control
  AgileAttacker *aa = static_cast<AgileAttacker*>(owner->attacker);

  // normal move
  if (dx != 0 || dy != 0) {
    engine.gameStatus=Engine::NEW_TURN;
    moveOrAttack(owner, owner->x+dx,owner->y+dy);
    engine.computeFov = true;
    // also update impulse
    aa->healImpulse();
    update_health(owner);
    return;
  }

  // linear change z level
  if (dz == 1) {
    engine.gameStatus=Engine::NEW_TURN;
    toggleZStatus(owner);
    // attack a creature if exists in this cell
    if (owner->z->onFloor) {
      aa->setAttackMode(DROP);
      moveOrAttack(owner, owner->x+dx,owner->y+dy);
      aa->setAttackMode(PUNCH);
    }
    update_health(owner);
    // also update impulse
    aa->healImpulse();
    return;
  }

  if (!aa->canAttack(mode)) {
    engine.gui->message(TCODColor::red, "You are too tired to do that.");
    return;
  }

  TCOD_key_t lastKey;
  // handle kick command
  if (mode == KICK) {
    // get kick direction
    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &lastKey, NULL, false);
    switch(lastKey.vk) {
      case TCODK_UP : dy=-1; break;
      case TCODK_DOWN : dy=1; break;
      case TCODK_LEFT : dx=-1; break;
      case TCODK_RIGHT : dx=1; break;
      default: break;
    }

    engine.gameStatus=Engine::NEW_TURN;
    if (owner->z->onFloor) {
      aa->setAttackMode(KICK);
      aa->processImpulseCost();
      moveOrAttack(owner, owner->x+dx,owner->y+dy);
      aa->setAttackMode(PUNCH);
    }
  }

  // Backhand the 2 locations to the left and right behind you
  if(mode == BACKHAND){
    // get direction you are facing
    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &lastKey, NULL, false);
    switch(lastKey.vk) {
      case TCODK_UP : dy=-1; break;
      case TCODK_DOWN : dy=1; break;
      case TCODK_LEFT : dx=-1; break;
      case TCODK_RIGHT : dx=1; break;
      default: break;
    }

    engine.gameStatus=Engine::NEW_TURN;
    if (owner->z->onFloor) {
      aa->setAttackMode(BACKHAND);
      aa->processImpulseCost();
      // save owner location
      int x = owner->x; int y = owner->y;
      // Backhand the 2 locations behind this direction
      // reset location after every attack
      if(dx==0){
	moveOrAttack(owner, owner->x+1,owner->y-dy);
	owner->x=x; owner->y=y;
	moveOrAttack(owner, owner->x-1,owner->y-dy);
	owner->x=x; owner->y=y;
      } else if(dy==0){
	moveOrAttack(owner, owner->x-dx,owner->y+1);
	owner->x=x; owner->y=y;
	moveOrAttack(owner, owner->x-dx,owner->y-1);
	owner->x=x; owner->y=y;
      }
      // handle diagonal cases eventually
      aa->setAttackMode(PUNCH);
    }
  }

  if(mode == POUND){
    engine.gameStatus=Engine::NEW_TURN;
    // save owner location
    int x = owner->x;
    int y = owner->y;
    if (owner->z->onFloor) {
      aa->setAttackMode(POUND);
      aa->processImpulseCost();
      // actual attacks
      for(int ix=-1;ix<=1;ix++)
	for(int iy=-1;iy<=1;iy++){
	  if(moveOrAttack(owner, owner->x+ix,owner->y+iy)){
	    // if true -> we were moved ->take us back to center
	    owner->x=x; owner->y=y;
	  }
	}
      aa->setAttackMode(PUNCH);
    }
    // add pound effect from ceiling
  }

  // verify if jump can be done
  // not on floor; cannot jump attack
  if (mode==JUMP && !owner->z->onFloor){
    engine.gui->message(TCODColor::red, "On ceiling; cannot jump.");
    return;
  }

  // verify if launch can be done
  // not on ceiling; cannot jump attack
  if (mode==LAUNCH && owner->z->onFloor){
    engine.gui->message(TCODColor::red, "On floor; cannot launch.");
    return;
  }
  // cannot launch from unstable location
  else if (mode==LAUNCH && !owner->z->isStable(owner)){
    engine.gui->message(TCODColor::red, "Need stable location to launch from.");
    return;
  }


  // combined handler for jump and launch
  if((mode==JUMP)||(mode==LAUNCH)){
    engine.computeFov = true;
    // get exact location
    int jx=0,jy=0;
    int done=false;
    while(!done){
      TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &lastKey, NULL, false);
      switch(lastKey.vk) {
	case TCODK_UP : jy+=-1; break;
	case TCODK_DOWN : jy+=1; break;
	case TCODK_LEFT : jx+=-1; break;
	case TCODK_RIGHT : jx+=1; break;
	case TCODK_ENTER : done=true; break;
	case TCODK_ESCAPE : return; break; // cancel turn
	default: break;
      }
      // to prevent going through walls
      if(engine.map->isWall(owner->x+jx, owner->y+jy)){
	// undo
	switch(lastKey.vk) {
	  case TCODK_UP : jy+=+1; break;
	  case TCODK_DOWN : jy+=-1; break;
	  case TCODK_LEFT : jx+=+1; break;
	  case TCODK_RIGHT : jx+=-1; break;
	  default: break;
	}
	// skip round
	continue;
      }
      engine.render();
      TCODConsole::root->setChar(owner->x+jx, owner->y+jy, 'X');
      TCODConsole::flush();
    }
    // location selected
    // TODO: check if location is reachable ie walls cannot be there blocking access; but enemies can

    engine.gameStatus=Engine::NEW_TURN;
    if (mode == JUMP){
      aa->setAttackMode(JUMP);
      aa->processImpulseCost();
    }
    else { // launch
      aa->setAttackMode(LAUNCH);
      aa->processImpulseCost();
      toggleZStatus(owner);
    }
    moveOrAttack(owner, owner->x+jx, owner->y+jy);
    aa->setAttackMode(PUNCH);
  }

  update_health(owner);
}

// probabilistically update health
void PlayerAi::update_health(Actor *owner){
  TCODRandom *rng=TCODRandom::getInstance();
  int h=rng->getInt(0, PLAYER_HEAL_ODDS);
  if(h==0){
    if (owner->destructible->hp + PLAYER_HEAL_AMT <= owner->destructible->maxHp){
      owner->destructible->hp += PLAYER_HEAL_AMT;
    } else {
      owner->destructible->hp = owner->destructible->maxHp;
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
	AgileAttacker *aa = static_cast<AgileAttacker*>(owner->attacker);
	aa->attack(owner, actor);
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

void PlayerAi::toggleZStatus(Actor *owner){
  owner->z->onFloor = !owner->z->onFloor;
  engine.gui->message(TCODColor::lightGrey, owner->z->onFloor ? "You drop down." : "You disappear into the ceiling.");
  // set player color according to z level
  owner->col = owner->z->onFloor ? TCODColor::white : TCODColor::black;
}
