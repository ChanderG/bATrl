#ifndef ENUM_H
#define ENUM_H

#include <string>
#include <map>

// Enum definitions

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

/* Messages list
 * Random strings that can be used to keep it interesting.
 * The corresponding size needs to be set correctly.
 */
const std::string AgileAttackCeilingCancelMessages[] = {
  						 "You attack the air.",
						 "What are you doing, Master Wayne?",
						 "Did you see a spider, Master Wayne?",
						 "I need to be careful when practicing midair.",
						 "You are on the ceiling; can't really do that.",
						 "I need to focus on the task at hand."
};
const int AgileAttackCeilingCancelMessagesSize = 6;

/*
 * Physiological states planned
 */
enum PhysiologicalState {
  NORMAL,
  ALERT,
  STUNNED,  // leads to entity not moving for a couple of turns
  CONFUSED, // leads to entity moving in the wrong direction
  AFRAID,   // leads to entity running away
  STARTLED  // leads to entity perform the next turn badly
};

const std::string PhysStateMessage[] = {"normal", "alert", "stunned", "confused", "afraid", "startled"};

enum RangedWeapon {
  NOWEAP,
  SHOTGUN,
  SMG
};

// Damages corrected for b@suit defense
const std::map<RangedWeapon, float> rangedWeaponDamages = {{NOWEAP, 0}, {SHOTGUN, 5}, {SMG, 10}};

#endif
