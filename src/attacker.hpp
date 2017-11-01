#ifndef ATTACKER_H
#define ATTACKER_H

#include "actor.hpp"
class Actor;

class Attacker {
public :
   float power; // hit points given

   Attacker(float power);
   void attack(Actor *owner, Actor *target);
};
#endif
