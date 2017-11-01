#include "engine.hpp"

Engine::Engine() : gameStatus(STARTUP){
  TCODConsole::initRoot(80,50,"libtcod C++ tutorial",false);
  player = new Actor(40,25,'@', "Batman", TCODColor::white);
  actors.push(player);

  map = new Map(80,45);
}

Engine::~Engine() {
  actors.clearAndDelete();
  delete map;
}

void Engine::update() {
  gameStatus = IDLE;

  TCOD_key_t key;
  int dx=0,dy=0;
  TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL);
  switch(key.vk) {
    case TCODK_UP : dy=-1; break;
    case TCODK_DOWN : dy=1; break;
    case TCODK_LEFT : dx=-1; break;
    case TCODK_RIGHT : dx=1; break;
    default:break;
  }

  if ( dx != 0 || dy != 0 ) {
    gameStatus=NEW_TURN;
    player->moveOrAttack(player->x+dx,player->y+dy);
  }

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
