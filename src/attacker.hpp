#ifndef ATTACKER_H
#define ATTACKER_H

#include <map>
#include <string>

#include "enum.hpp"
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

class AgileAttacker : public Attacker {
  public:
    std::map<AgileAttack, float> powerMap; // capability of each attack
    std::map<AgileAttack, std::string> msgMap; // message displayed for each attack
    AgileAttack attackMode; // current attack mode
    
    float maxImpulse;
    float currentImpulse;
    std::map<AgileAttack, float> impulseMap; // implulse required for each attack

    AgileAttacker();
    void setAttackMode(AgileAttack mode);  // set attack mode for the next attack
    void attack(Actor *owner, Actor *target);
    void postAttack(Actor *owner, Actor *target); // post attack effects
    bool canAttack(AgileAttack mode); // can we use mode attack at current impulse levels?
    void healImpulse(); // restore impulse levels
    void processImpulseCost(); // account impulse costs
};

#endif
