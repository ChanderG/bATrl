#include "physiology.hpp"

// Constructor -> all entities start at normal state
Physiology::Physiology(){
  currStateTimeout = 0;
  currPhysState = NORMAL;
}

/*
 * Internal update -> run once per turn for all units.
 * Heal/Correct previous effects basically here.
 *
 * For now, all non NORMAL effects heal up -> move timeout 0. If reached 0; back to normal.
 * Over time, the effect wears out and you are back to normal.
 */
void Physiology::update_internal(Actor *owner){
  if(currStateTimeout > 0) currStateTimeout--;

  if ((currStateTimeout==0) && (currPhysState!=NORMAL)){
    currPhysState = NORMAL;
    render_phys_state(owner);
  }
}

/*
 * Called when attacked by external entity.
 *
 * Update physiological effect probabilistically based on attack.
 */
void Physiology::update_external_attack(Actor* owner, AgileAttack mode){
  TCODRandom *rng=TCODRandom::getInstance();

  switch(mode){

    case PUNCH: {
		  int chance = rng->getInt(0,100);
		  // 10 % chance of getting stunned for 2 turns
		  if(chance < 10){
		    currPhysState = STUNNED;
		    currStateTimeout = 3;
		    render_phys_state(owner);
		  }
		  // 10 % chance of getting confused for 2 turns
		  else if(chance < 20){
		    currPhysState = CONFUSED;
		    currStateTimeout = 3;
		    render_phys_state(owner);
		  }
		  // no other effects
		  break;
		}

    case KICK: {
		 int chance = rng->getInt(0,100);
		 // 30% chance of getting stunned for 3 turns
		 if(chance < 30){
		   currPhysState = STUNNED;
		   currStateTimeout = 4;
		   render_phys_state(owner);
		 }
		 // no other effects
		 break;
	       }

    case DROP: {
		 int chance = rng->getInt(0,100);
		 // 30 % chance of getting stunned for 4 turn
		 if(chance < 30){
		   currPhysState = STUNNED;
		   currStateTimeout = 5;
		   render_phys_state(owner);
		 }
		 // no other effects
		 break;
	       }

    case BACKHAND: break;

    case POUND: {
		  int chance = rng->getInt(0,100);
		  // 5% chance of getting stunned for 3 turns
		  if(chance < 5){
		    currPhysState = STUNNED;
		    currStateTimeout = 4;
		    render_phys_state(owner);
		  }
		  // 25% chance of getting confused for 2 turns
		  else if(chance < 30){
		    currPhysState = CONFUSED;
		    currStateTimeout = 3;
		    render_phys_state(owner);
		  }
		  // 10% chance of getting afraid for 5 turns
		  else if(chance < 40){
		    currPhysState = AFRAID;
		    currStateTimeout = 6;
		    render_phys_state(owner);
		  }
		  // no other effects
		  break;
		}

    case JUMP: {
		 int chance = rng->getInt(0,100);
		 // 20 % chance of getting stunned for 2 turns
		 if(chance < 20){
		   currPhysState = STUNNED;
		   currStateTimeout = 3;
		   render_phys_state(owner);
		 }
		 // no other effects
		 break;
	       }

    case LAUNCH: {
		   int chance = rng->getInt(0,100);
		   // 30% chance of getting stunned for 3 turns
		   if(chance < 30){
		     currPhysState = STUNNED;
		     currStateTimeout = 4;
		     render_phys_state(owner);
		   }
		   // 5% chance of getting afraid for 2 turns
		   else if(chance < 35){
		     currPhysState = AFRAID;
		     currStateTimeout = 3;
		     render_phys_state(owner);
		   }
		   // no other effects
		   break;
		 }

    case FLIP: {
		 int chance = rng->getInt(0,100);
		 // 75 % chance of getting stunned for 5 turns
		 if(chance < 75){
		   currPhysState = STUNNED;
		   currStateTimeout = 6;
		   render_phys_state(owner);
		 }
		 // 20% chance of getting stunned for 2 turns
		 else if (chance < 95) {
		   currPhysState = STUNNED;
		   currStateTimeout = 3;
		   render_phys_state(owner);
		 }
		 // 5% chance of failing
		 // no other effects
		 break;
	       }

    default: break;

  }

  if(currPhysState != NORMAL){
    engine.gui->message(TCODColor::blue, "The %s is %s!", owner->name, PhysStateMessage[currPhysState].c_str());
  }
}

/*
 * Process effects of current physiological state.
 *
 * Returns false, if further action/intent can be proceeded with.
 * If true => the physiological state is too much to further perform any intent.
 */
bool Physiology::process_current_state(Actor *owner){
  TCODRandom *rng=TCODRandom::getInstance();

  switch (currPhysState){
    case NORMAL: return false;

    case STUNNED:{
		   // cannot really move or attack
		   return true;
		 }

    case CONFUSED:{
		    // move in random direction
		    ((MonsterAi*)(owner->ai))->moveOrAttack(owner, owner->x+rng->getInt(-1,1), owner->y+rng->getInt(-1, 1));
		    return true;
		  }

    case AFRAID:{
		  // move away from the player
		  // TODO
		  return true;
		}

    case STARTLED:{
		    // affect performance
		    // TODO
		    return false;
		  }

    default: break;
  }
  return false;
}

/*
 * Set background of actor to display effect.
 *
 * Called automatically whenever the phsyiological state changes.
 */
void Physiology::render_phys_state(Actor *owner){
  switch(currPhysState){
    case NORMAL: owner->bgcol = TCODColor::black; break;
    case STUNNED: owner->bgcol = TCODColor::orange; break;
    case CONFUSED: owner->bgcol = TCODColor::yellow; break;
    case AFRAID: owner->bgcol = TCODColor::red; break;
    case STARTLED: owner->bgcol = TCODColor::pink; break;
    default: break;
  }
}
