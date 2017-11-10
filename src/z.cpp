#include "z.hpp"

// is the owner in a stable location as far as Z is concerned
// For now:
// STABLE - adjacent to any wall
// UNSTABLE - not adjacent to any wall
//
// Defn will grow with the intro of height based objects
//
// Uses of stability:
// For attacks -> for example need stable location to launch from for glide kick type attack.
// For using equipment such as throwing b@rangs, you need a stable location.
bool Z::isStable(Actor *owner){
  for(int dx=-1; dx <= 1; dx++)
    for(int dy=-1; dy <= 1; dy++){
      // one of the adj locations is a wall
      if(engine.map->isWall(owner->x+dx, owner->y+dy)){
	return true;
      }
    }

  return false;
}
