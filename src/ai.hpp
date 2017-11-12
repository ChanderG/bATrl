#ifndef AI_H
#define AI_H

#include <stack>

#include "actor.hpp"
#include "engine.hpp"
#include "physiology.hpp"
#include "enum.hpp"
#include "intent.hpp"

class Intent;
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
   MonsterAi(RangedWeapon weap);
   void update(Actor *owner);
   Physiology *phys;
   RangedWeapon weap;
   std::stack<Intent*> intents;

   void moveOrAttack(Actor *owner, int targetx, int targety);
   void move(Actor *owner, int targetx, int targety);
};

#endif
