#ifndef MAP_H
#define MAP_H

struct Tile {
  bool explored; // has the player already seen this tile ?
  Tile() : explored(false) {}
};

class Map {
  public :
    int width,height;

    Map(int width, int height);
    ~Map();
    bool isWall(int x, int y) const;
    void render() const;
    bool canWalk(int x, int y) const;  
    void addMonster(int x, int y);
    bool isInFov(int x, int y) const;
    bool isInFoa(int x, int y) const;
    bool isExplored(int x, int y) const;
    void computeFov();

  protected :
    Tile *tiles;
    TCODMap *map;
    friend class BspListener;

    void dig(int x1, int y1, int x2, int y2);
    void createRoom(bool first, int x1, int y1, int x2, int y2);
};
#endif
