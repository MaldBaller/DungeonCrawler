// background.h
#include "tile.h"

class Background {
public:
    Vector2 tiles[0] = {};
    int level;
    
    Background(int lvl) {
        level = lvl;
    }
};
