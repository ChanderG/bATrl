#ifndef ENUM_H
#define ENUM_H

#include <string>

// Enum definittions

/*
 * The attacks have varying impact on HP. But more importantly, they have varying effects
 * such as Area of Effect, Displacing the enemy and other enemy physiological effects.
 *
 * Also planned are varying enemy types that have varying response to attacks - for example,
 * some attacks aimed towards peeling of armour from enemy, some designed to disarm enemies
 * etc.
 *
 * The physiological responses are captured in physiology.cpp whereas the hp damage is captured in attacker.cpp.
 */
enum AgileAttack {
  NONE,
  PUNCH,
  KICK,
  DROP,
  BACKHAND,
  POUND,
  JUMP,
  LAUNCH,
  FLIP
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
