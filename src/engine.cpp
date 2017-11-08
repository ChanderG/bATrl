#include "engine.hpp"

Engine::Engine(int screenWidth, int screenHeight) : gameStatus(STARTUP), screenWidth(screenWidth), screenHeight(screenHeight), fovRadius(6), foaRadius(10), computeFov(true){
  TCODConsole::setCustomFont("terminal.png", TCOD_FONT_LAYOUT_ASCII_INROW, 16, 16);
  TCODConsole::initRoot(screenWidth, screenHeight, "b@rl",false);

  // create player
  player = new Actor(40,25,'B', "Batman", TCODColor::white);
  player->destructible=new PlayerDestructible(30,2,"your cadaver");
  player->attacker=new AgileAttacker();
  player->ai = new PlayerAi();
  player->z = new Z();
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

/*
 * Show starting splash screen,
 */
void Engine::showSplashScreen(){

  char title[] = "b@rl";
  TCODConsole::root->print(screenWidth/2, screenHeight/4, title);
  char msg[] = "Press any key to continue.";
  TCODConsole::root->print(screenWidth/4, 3*screenHeight/4, msg);
  TCODConsole::flush();
  TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, NULL, NULL, false);
}

void Engine::update() {
  gameStatus = IDLE;

  TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &lastKey, NULL, false);
  player->update();

  if(computeFov){
    map->computeFov();
    computeFov=false;
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
    Actor *actor=*iterator;
    // audio field is larger than the vision field
    if ( map->isInFoa(actor->x,actor->y) ) {
      actor->render();
    }
  }
  // show the player's stats
  gui->render();
}

void Engine::sendToBack(Actor *actor) {
  actors.remove(actor);
  actors.insertBefore(actor,0);
}
