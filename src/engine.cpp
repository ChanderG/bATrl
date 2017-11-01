#include "engine.hpp"

Engine::Engine(int screenWidth, int screenHeight) : gameStatus(STARTUP), screenWidth(screenWidth), screenHeight(screenHeight){
  TCODConsole::initRoot(screenWidth, screenHeight, "libtcod C++ tutorial",false);
  TCODConsole::root->setDefaultForeground(TCODColor::white);
  player = new Actor(40,25,'@', "Batman", TCODColor::white);
  player->destructible=new PlayerDestructible(30,2,"your cadaver");
  player->attacker=new Attacker(5);
  player->ai = new PlayerAi();
  actors.push(player);

  map = new Map(screenWidth, screenHeight - 5);
}

Engine::~Engine() {
  actors.clearAndDelete();
  delete map;
}

void Engine::update() {
  gameStatus = IDLE;

  TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &lastKey, NULL);
  player->update();
  // show the player's stats
  TCODConsole::root->print(1, screenHeight - 2, "HP : %d/%d",
      (int)player->destructible->hp,(int)player->destructible->maxHp);

  if ( gameStatus == NEW_TURN ) {
    for (Actor **iterator=actors.begin(); iterator != actors.end();
	iterator++) {
      Actor *actor=*iterator;
      if ( actor != player ) {
	actor->update();
      }
    }
  }

}

void Engine::render() {
  TCODConsole::root->clear();
  // draw the map
  map->render();
  // draw the actors
  for (Actor **iterator=actors.begin(); iterator != actors.end(); iterator++) {
    (*iterator)->render();
  }
}

void Engine::sendToBack(Actor *actor) {
  actors.remove(actor);
  actors.insertBefore(actor,0);
}
