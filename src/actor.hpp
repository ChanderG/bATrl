class Actor {
  public:
    int x,y; // position
    int ch;  // code repn the actor
    TCODColor col; // col of character

    Actor(int x, int y, int ch, const TCODColor &col);
    void render() const;
};
