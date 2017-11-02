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
  powerMap[KICK] = 10;
  powerMap[DROP] = 15;

  msgMap[PUNCH] = "You punch";
  msgMap[KICK] = "You kick";
  msgMap[DROP] = "You land on and force down";

  setAttackMode(PUNCH);
}

void AgileAttacker::setAttackMode(AgileAttack mode){
  power = powerMap[mode];
  attackMsg = msgMap[mode];
}
