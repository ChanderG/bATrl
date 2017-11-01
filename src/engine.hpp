#ifndef ENGINE_H
#define ENGINE_H

#include "libtcod.hpp"
#include "actor.hpp"
#include "map.hpp"
#include "gui.hpp"

class Engine {
  public :
    TCODList<Actor *> actors;
    Actor *player;
    Map *map;
    enum GameStatus {
      STARTUP,
      IDLE,
      NEW_TURN,
      VICTORY,
      DEFEAT
    } gameStatus;
    int screenWidth;
    int screenHeight;
    TCOD_key_t lastKey;
    Gui *gui;

    Engine(int screenWidth, int screenHeight);
    ~Engine();
    void update();
    void render();
    void sendToBack(Actor *actor);
};

extern Engine engine;
#endif
