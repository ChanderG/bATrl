#ifndef ACTOR_H
#define ACTOR_H

class Actor {
  public:
    int x,y; // position
    int ch;  // code repn the actor
    TCODColor col; // col of character
    const char* name;

    Actor(int x, int y, int ch, const char* name, const TCODColor &col);
    void render() const;
    void update();
    bool moveOrAttack(int x, int y);
};

#endif
