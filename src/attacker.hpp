#ifndef ATTACKER_H
#define ATTACKER_H

#include <map>
#include <string>

#include "actor.hpp"
class Actor;

class Attacker {
public :
   float power; // hit points given
   std::string attackMsg;

   Attacker(float power);
   Attacker(); // empty constructor for children class use
   void attack(Actor *owner, Actor *target);
};

enum AgileAttack {
  PUNCH,
  KICK,
  DROP
}; 

class AgileAttacker : public Attacker {
  public:
    std::map<AgileAttack, float> powerMap; // capability of each attack
    std::map<AgileAttack, std::string> msgMap; // capability of each attack
    AgileAttack attackMode;

    AgileAttacker();
    void setAttackMode(AgileAttack mode);  // set attack mode for the next attack
    void attack(Actor *owner, Actor *target);
    void postAttack(Actor *owner, Actor *target);
};

#endif
