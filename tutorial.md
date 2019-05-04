# Tutorial
(or)
How to become the b@t.

(upto date with master)

Disclaimer: The Overview section talks from the perspective of the long term planned features of this game, not what exists currently. While I have clear ideas for the future versions and scope, whether and when I will get to them is a function of time and interest.

## Overview

b@rl is a roguelike version of Batman focussed on combat. What this means is:

1. Permadeath -> Unlike the comic version of Batman, the b@t can die. When this happens, everything is lost, there is no savegame. Quite like real life.
2. Randomized Procedural generation -> Building, floor plans, cities are generated randomly, no two playthroughs will be alike. Ideally, (maybe eventually) combat moves, equipment etc should also be randomly generated.
3. Quantized Time/Space -> Meaning Tile based and Turn based. Tile based allows simplification of concepts and turn based allows players to focus on tactics rather than play by reflex.

### How does it differ from all the other Batman games?

The ethos of playing Batman (or any other superhero) is the feeling of power and absolutely domination of everything on the field. 

While other games do convey this feeling, it is mostly an illusion due to the lack of permaconsequence. You are going to go through the levels and can die any number of times with any boss. To make it realistic, we need to add in a bunch of features that will now allow the player to get into situations he cannot escape from unscathed.

So how does the combat differ? You still play the b@t and hence have access to a bunch of dynamic moves jumping from enemy to enemy, hiding in the rafters, kicking an henchmen and sending him sprawling. 

However, you now have an impulse bar that limits the number of dynamic movements you can do sequentially and the b@t will tire down. Similarly, guns in this game (shockingly) have real impact and your enemies are not Stormtroopers. Armed enemies will shoot you and the damage dealt is enough to severly impact even the b@t. (Irrespective of what the normal games claim, Batman's normal suit won't bounce off bullets and the thugs are not going to miss from a distance of a few metres).

### How does it differ from all the other Roguelikes?

If you are a Roguelike player, be warned, the current game will disappoint you.

The combat is something not seen before in the roguelike genre. I take elements of Sil's tactical positioning, DoomRL's play style and add in more dynamism to try to capture the power of Batman. Whether this works well is something you will have play and find out.

Very few elements of the game are (currently) procedurally generated. I have not planned a general solution to this issue. One of the core elements of a Roguelike is how much chance controls a playthrough. Finding a single artifact sword or armour can completely change your planning. I intend to add in some such elements of chance down the line (in terms of what equipment is available to the b@t), but most of the playstyle would be based around the Batman mythos. I understand that this is not good enough, actively searching for ways to allow randomness to control playthroughs more.

Additionally, the planned future of the game would be with an city Overworld that itself is procedurally generated. This is slightly different from classicaly roguelikes that have a static overworld (ADOM, Maj'Eyal) if at all.

## The World

Currently, the world is a single floor filled with rooms containing bad guys. Your mission is to take them all out without dying yourself!!!

To give some idea of the full world in scope:

1. What you currently see is a single floor of a single building in a city. As you are the b@t, you can walk on the floor or crawl on the ceiling/rafters unobserved by your enemies.
2. Batman enters the building either from the roof or the ground floor and has to get to a destined floor to capture a badguy/free some hostages etc.
3. The outside and the inside of the building will be defined eventually allowing the b@t to sneak around outside floors and finding the best point of entry.
4. Beyond all of this, the overview map would be procedurally generated per game, creating an unique Gotham/Arkham for the b@t to roam around and enter said building. Buildings will be generated with random exterior shapes, the floor plan exteriors matching on each floor.

## Playing the b@t

You control the b@t, a powerful entity shrouded in darkness. 

### Moving

The initial moveset of the player is:

1. Arrow keys to move around.
2. Space to jump from floor to ceiling (imagine using a grappling hook) and dropping from ceiling to floor. Once on the ceiling, the player can move around unseen by the room occupants (it's dark up there). Ceiling positions are divided into 2 categories, stable (adjacent to any wall) and non-stable (not adjacent to any wall). This impacts what can be done from what location.

### Health and Stamina

The player has 2 bars:
1. Health bar -> health of the b@t, game over if this reaches 0, regenerates slowly
2. Impulse bar -> stamina levels, impacts allowed combat moves, regenerates slowly

### Combat

1. Arrow keys onto tiles with enemies, punch them.
2. k followed by <dir key>: kick an enemy, send the enemy sprawling backward, extra damage is done if enemy hits a wall, the kick can be cascading too, if the enemy shoves against another entity, the other entity will also be sent sprawling backwards
3. p: Sends a shockwave into the ground, knocks all surrounding enemies backward by a couple of tiles. Consumes a lot of impulse.
4. b followed by <dir key>: backhand enemies. Backhand an enemy behind you (ie in the position diagonal opposite of input direction). Since it's batman, he can double backhand and simultaneously hit enemies on both the diagonal tiles.
5. j followed by tile selection: Jump tackle enemies across the room. Consumes impulse based on distance. High chance of startling all observers.
6. l followed by tile selection: Launch from the ceiling into an enemy across the room. Can only be done from stable ceiling positions. Consumes lesser impulse but does more damage.
7. space when on the ceiling on top of an enemy: drop on the unsuspecting enemy, does a lot of damage
8. f followed by <dir key>: Flip an enemy (imagine that the b@t grabs enemies by the head and knocks them over). Does some damage and compulsorily Stuns the enemy.

All attacks reduce enemy hitpoints and have a chance of inducing one of enemy status effects. For eg, Jumping from enemy to enemy startles all observers, increacing the chance of gun shots missing. Very useful when there is a bunch of armed henchmen shooting at you. However, jumping costs the most stamina and can lead to the b@t tiring out quickly.

## Monsters

(currently all human, but called this for historical reasons)

### Monster Types

### Monster Actions

### Monster Status Effects

Apart from the health of monsters, they also have the following status effects, allowing variety in gameplay:

1. Unaware: initial state, take extra damage when attacked
2. Alert: Has spotted the b@t and heading to attack
3. Stunned: Spend the next couple of turns stationary trying to get back on their feet
4. Confused: Spends the next few turns moving in random directions.
5. Afraid: Runs away from the b@t
6. Startled: Perform the next turn badly, for eg. miss melee and ranged attacks.
