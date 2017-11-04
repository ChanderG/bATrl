#include "attacker.hpp"

#include <cstdio>

Attacker::Attacker(float power) : power(power) {
}

Attacker::Attacker(){
}

void Attacker::attack(Actor *owner, Actor *target) {

  if ( target->destructible && ! target->destructible->isDead() ) {
    if ( power - target->destructible->defense > 0 ) {
      if (owner == engine.player) engine.gui->message(TCODColor::white, "%s the %s", attackMsg.c_str(), target->name);
      engine.gui->message(owner==engine.player ? TCODColor::red : TCODColor::lightGrey , "%s loses %g hit points.", target->name,
	  power - target->destructible->defense);
    } else {
      engine.gui->message(TCODColor::lightGrey, "%s attacks %s but it has no effect!", owner->name, target->name);
    }
    target->destructible->takeDamage(target,power);
  } else {
    engine.gui->message(TCODColor::lightGrey, "%s attacks %s in vain.",owner->name,target->name);
  }
}

AgileAttacker::AgileAttacker() : Attacker::Attacker() {
  powerMap[PUNCH] = 5;
  powerMap[KICK] = 7;
  powerMap[DROP] = 15;
  powerMap[BACKHAND] = 5;
  powerMap[POUND] = 6;

  msgMap[PUNCH] = "You punch";
  msgMap[KICK] = "You kick";
  msgMap[DROP] = "You land on and force down";
  msgMap[BACKHAND] = "You backhand";
  msgMap[POUND] = "Your pound smacks";

  setAttackMode(PUNCH);
}

void AgileAttacker::setAttackMode(AgileAttack mode){
  power = powerMap[mode];
  attackMsg = msgMap[mode];
  attackMode = mode;
}

void AgileAttacker::attack(Actor *owner, Actor *target) {
  Attacker::attack(owner, target);
  // post attack processing
  postAttack(owner, target);
}

void AgileAttacker::postAttack(Actor *owner, Actor* target){
  if (attackMode == KICK){
    // note down target location
    int tx = target->x;
    int ty = target->y;

    // displace the target
    int effect = 4;
    int dx = (owner->x > target->x) ? -1 : (owner->x < target->x) ? +1 : 0;
    int dy = (owner->y > target->y) ? -1 : (owner->y < target->y) ? +1 : 0;
    target->displace(dx*effect, dy*effect);

    // also move into target location
    owner->x = tx;
    owner->y = ty;
  }
  else if (attackMode == POUND){
    // similar to kick

    // displace the target
    int effect = 2;
    int dx = (owner->x > target->x) ? -1 : (owner->x < target->x) ? +1 : 0;
    int dy = (owner->y > target->y) ? -1 : (owner->y < target->y) ? +1 : 0;
    target->displace(dx*effect, dy*effect);

    // no displacement for ourselves
  }
}
