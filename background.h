// background.h
#include "tile.h"
#include <vector>

class Background {
public:
    std::vector<Tile> tiles;
    int level;

    Background(int lvl) {
        level = lvl;
    }
};
