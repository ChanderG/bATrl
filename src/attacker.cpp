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

/*
 * Init the various variables relating to an agile attacker.
 */
AgileAttacker::AgileAttacker() : Attacker::Attacker() {
  powerMap[PUNCH] = 5;
  powerMap[KICK] = 7;
  powerMap[DROP] = 15;
  powerMap[BACKHAND] = 5;
  powerMap[POUND] = 6;
  powerMap[JUMP] = 8;
  powerMap[LAUNCH] = 8;

  msgMap[PUNCH] = "You punch";
  msgMap[KICK] = "You kick";
  msgMap[DROP] = "You take down";
  msgMap[BACKHAND] = "You backhand";
  msgMap[POUND] = "Your pound smacks";
  msgMap[JUMP] = "You jump into";
  msgMap[LAUNCH] = "You launch into";

  maxImpulse = 30;
  currentImpulse = maxImpulse;

  impulseMap[PUNCH] = 0;
  impulseMap[KICK] = 2;
  impulseMap[DROP] = 2;
  impulseMap[BACKHAND] = 0;
  impulseMap[POUND] = 12;
  impulseMap[JUMP] = 3;
  impulseMap[LAUNCH] = 2;

  setAttackMode(PUNCH);
}

void AgileAttacker::setAttackMode(AgileAttack mode){
  power = powerMap[mode];
  attackMsg = msgMap[mode];
  attackMode = mode;
}

void AgileAttacker::attack(Actor *owner, Actor *target) {
  // base class attack processing to avoid duplication
  Attacker::attack(owner, target);
  // post attack processing
  postAttack(owner, target);
  // phsyiological impact on target
  ((MonsterAi*)(target->ai))->phys->update_external_attack(target, attackMode);
}

/*
 * Needs to be called exactly once for each attack type.
 */
void AgileAttacker::processImpulseCost(){
  // process impulse cost for all attack types
  currentImpulse -= impulseMap[attackMode];
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
  else if (attackMode == JUMP){
    // go to target location
    owner->x = target->x;
    owner->y = target->y;
  }
  else if (attackMode == LAUNCH){
    // note down target location
    int tx = target->x;
    int ty = target->y;

    // displace the target slightly
    int effect = 1;
    int dx = (owner->x > target->x) ? -1 : (owner->x < target->x) ? +1 : 0;
    int dy = (owner->y > target->y) ? -1 : (owner->y < target->y) ? +1 : 0;
    target->displace(dx*effect, dy*effect);

    // also move into target location
    owner->x = tx;
    owner->y = ty;
  }
}

// can we use mode attack at current impulse levels?
bool AgileAttacker::canAttack(AgileAttack mode){
  if (currentImpulse >= impulseMap[mode]){
    return true;
  }
  return false;
}

void AgileAttacker::healImpulse(){
  if(currentImpulse == maxImpulse){
    return;
  }
  // simple increment for now
  currentImpulse++;
  if(currentImpulse > maxImpulse){
    currentImpulse = maxImpulse;
  }
}
