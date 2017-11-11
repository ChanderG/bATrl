#ifndef PHYSIOLOGY_H
#define PHYSIOLOGY_H

#include "enum.hpp"
#include "actor.hpp"

/*
 * Models physiology of a LIVING ENTITY.
 * Designed to be used for enemies. 
 *
 * Right, now ties into the owner heavily. Needs to be generalized if needed.
 * Eventually, needs to be used with the player as well.
 *
 * Also individual unit physiology is to be modelled -> right now all entities have the same reaction.
 */
class Physiology{
  public:
    PhysiologicalState currPhysState;  // current state 
    int currStateTimeout;

    Physiology();
    void update_internal(Actor *owner);
    void update_external_attack(Actor *owner, AgileAttack mode);
    bool process_current_state(Actor *owner);

    void render_phys_state(Actor *owner);
};

#endif
