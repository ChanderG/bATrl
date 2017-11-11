#ifndef AI_H
#define AI_H

#include "actor.hpp"
#include "engine.hpp"
#include "physiology.hpp"

class Physiology;

class Ai {
public :
   virtual void update(Actor *owner)=0;
};

class PlayerAi : public Ai {
public :
   PlayerAi();
   void update(Actor *owner);

protected :
   bool moveOrAttack(Actor *owner, int targetx, int targety);
   void toggleZStatus(Actor *owner);
   void update_health(Actor *owner);
};

class MonsterAi : public Ai {
public :
   MonsterAi();
   void update(Actor *owner);
   Physiology *phys;
   void moveOrAttack(Actor *owner, int targetx, int targety);
};

#endif
