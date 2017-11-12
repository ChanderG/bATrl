#ifndef INTENT_H
#define INTENT_H

#include "actor.hpp"

/*
 * Intent is the general superclass for enemy actions.
 *
 * All enemies need to have a stack of intents.
 * Intents can be turn limited or infinitely long.
 *
 * Intents should be cancellable as well. 
 * 
 * All these related stuff currently are NOT covered in class.
 *
 * NOTE: attack should eventually come under the intent system. Ideally so should Physiology,
 * but that requires multiple intents interacting, which may not be easily doable.
 */
class Intent {
  public:
    virtual void carryOutIntent(Actor *owner) = 0; // actual action carried out
    virtual bool isDone() = 0; // whether this intent can be destroyed
    virtual ~Intent();
};

/*
 * Stay intent: stay at spawn location forever
 */
class StayIntent : public Intent {
  public:
    StayIntent(Actor *owner);
    void carryOutIntent(Actor *owner);
    bool isDone();
    ~StayIntent();
};

class PatrolIntent: public Intent {
private:
    int origx, origy; 
    int destx, desty;
    bool awayPhase;

public:
    PatrolIntent(Actor *owner);
    void carryOutIntent(Actor *owner);
    bool isDone();
    ~PatrolIntent();
};

// More intents to come here...
// See todo.txt for som examples.

#endif
