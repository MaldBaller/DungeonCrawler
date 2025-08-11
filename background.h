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
        std::vector<Vector2> occupiedPositions = {};

        Tile startingTile(0, {width/2, height/2});
        tiles.push_back(startingTile);
        occupiedPositions.push_back(startingTile.position);

        bool isStillGenerating = true;
        while(isStillGenerating) {
            for(const Tile& i : tiles) {
                // Generate tile above if applicable
                // Generate tile to right if applicable
                // Generate tile below if applicable
                // Generate tile to left if applicable
            }
        }
    }
};
