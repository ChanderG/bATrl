#include "libtcod.hpp"
#include "actor.hpp"
#include "map.hpp"
#include "engine.hpp"

Engine engine(80, 50);

int main(){
  // show init splash screen
  engine.showSplashScreen();
  // draw the map etc for the first turn w/o user input
  engine.render();
  TCODConsole::flush();
  // start the main loop
  while( !TCODConsole::isWindowClosed()){
    engine.update();
    engine.render();
    TCODConsole::flush();
  }
  return 0;
}
