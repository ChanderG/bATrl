#include "engine.hpp"

Engine::Engine(int screenWidth, int screenHeight) : gameStatus(STARTUP), screenWidth(screenWidth), screenHeight(screenHeight){
  TCODConsole::setCustomFont("terminal.png", TCOD_FONT_LAYOUT_ASCII_INROW, 16, 16);
  TCODConsole::initRoot(screenWidth, screenHeight, "libtcod C++ tutorial",false);

  // create player
  player = new Actor(40,25,'B', "Batman", TCODColor::white);
  player->destructible=new PlayerDestructible(30,2,"your cadaver");
  player->attacker=new Attacker(5);
  player->ai = new PlayerAi();
  actors.push(player);

  map = new Map(screenWidth, screenHeight - 7);
  gui = new Gui();

  gui->message(TCODColor::yellow, "Welcome back, Master Wayne.\n How was your vacation?");
}

Engine::~Engine() {
  actors.clearAndDelete();
  delete map;
  delete gui;
}

void Engine::update() {
  gameStatus = IDLE;

  TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &lastKey, NULL);
  player->update();

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
  // show the player's stats
  gui->render();
}

void Engine::sendToBack(Actor *actor) {
  actors.remove(actor);
  actors.insertBefore(actor,0);
}
