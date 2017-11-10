#ifndef Z_H
#define Z_H 

#include "actor.hpp"

class Z{
  public:
    bool onFloor;

    // default to starting on the floor
    Z(): onFloor(true){}
    bool isStable(Actor *owner); // are we in a stable pose
};

#endif 
