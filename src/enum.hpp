#ifndef ENUM_H
#define ENUM_H

#include <string>

// Enum definittions

enum AgileAttack {
  NONE,
  PUNCH,
  KICK,
  DROP,
  BACKHAND,
  POUND,
  JUMP,
  LAUNCH
}; 

/*
 * Physiological states planned
 */
enum PhysiologicalState {
  NORMAL,
  STUNNED,  // leads to entity not moving for a couple of turns
  CONFUSED, // leads to entity moving in the wrong direction
  AFRAID,   // leads to entity running away
  STARTLED  // leads to entity perform the next turn badly
};

const std::string PhysStateMessage[] = {"normal", "stunned", "confused", "afraid", "startled"};

#endif
