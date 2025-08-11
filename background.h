// background.h
#pragma once
#include "tile.h"
#include <vector>

class Background {
public:
    std::vector<Tile> tiles;
    int level;
    int height;
    int width;

    Background(int lvl, int hei, int wid) {
        level = lvl;
        height = hei;
        width = wid;
    }

    void Generate() {
        Tile startingTile(0, {width/2, height/2});
        tiles.push_back(startingTile);
    }
};
