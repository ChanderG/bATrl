#include "ai.hpp"

#include <cmath>

MonsterAi::MonsterAi() {
  // create 1 size fits all physiological model
  phys = new Physiology();
}

/*
 * Monster Ai stuff.
 * Not really monster -> just human.
 * Name left in for legacy reasons.
 */
void MonsterAi::update(Actor *owner) {
  if ( owner->destructible && owner->destructible->isDead() ) {
    // remove all physiological effects
    phys->currPhysState = NORMAL;
    phys->render_phys_state(owner);
    return;
  }
  // update physiological effects
  phys->update_internal(owner);

  // process physiological effect
  int physEventProcessed = phys->process_current_state(owner);
  // if proceessed and overwhelmed exit
  if(physEventProcessed == true) return;

  // only if player is on floor and in line of sight
  if ((engine.player->z->onFloor) && engine.map->isInFov(owner->x,owner->y)) {
    moveOrAttack(owner, engine.player->x,engine.player->y);
  }
}

void MonsterAi::moveOrAttack(Actor *owner, int targetx, int targety) {
  int dx = targetx - owner->x;
  int dy = targety - owner->y;
  int stepx = (dx > 0 ? 1:-1);
  int stepy = (dy > 0 ? 1:-1);
  float distance=sqrtf(dx*dx+dy*dy);
  if ( distance >= 2 ) {
    dx = (int)(round(dx/distance));
    dy = (int)(round(dy/distance));
    if ( engine.map->canWalk(owner->x+dx,owner->y+dy) ) {
      owner->x += dx;
      owner->y += dy;
    } else if ( engine.map->canWalk(owner->x,owner->y+stepy) ) {
      owner->y += stepy;
    } else if ( engine.map->canWalk(owner->x+stepx,owner->y) ) {
      owner->x += stepx;
    }
  } else if ( owner->attacker ) {
    owner->attacker->attack(owner,engine.player);
  }
}
