#include "intent.hpp"

Intent::~Intent() {
}

StayIntent::StayIntent(Actor *owner) {
}

/*
 * As such, nothing to do.
 */
void StayIntent::carryOutIntent(Actor *owner) {
  return;
}

/*
 * Always runs.
 */
bool StayIntent::isDone(){
  return false;
}

/*
 * Kinda dummy.
 */
StayIntent::~StayIntent(){
  return;
}

/*
 * Randomly generate pace path.
 */
PatrolIntent::PatrolIntent(Actor *owner){
  origx = owner->x;
  origy = owner->y;

  // choose endpoint
  TCODRandom *rng=TCODRandom::getInstance();
  while(true){
    destx = origx + rng->getInt(-15, 15);
    desty = origy + rng->getInt(-15, 15);
    if(destx > engine.map->width || destx < 0) continue;
    if(desty > engine.map->height || desty < 0) continue;
    if (!engine.map->isWall(destx, desty)) break;
  }

  awayPhase = true;
}

/*
 * Go towards the other endpoint.
 * Dumb right now -> will attack even allies in the way.
 */
void PatrolIntent::carryOutIntent(Actor *owner) {
  if(awayPhase){
    ((MonsterAi*)owner->ai)->move(owner, destx, desty);
    if(owner->x==destx && owner->y==desty){
      awayPhase = false;
    }
  } else {
    ((MonsterAi*)owner->ai)->move(owner, origx, origy);
    if(owner->x==origx && owner->y==origy){
      awayPhase = true;
    }
  }
}

/*
 * Keep running.
 */
bool PatrolIntent::isDone(){
  return false;
}

// Dummy.
PatrolIntent::~PatrolIntent(){
}
