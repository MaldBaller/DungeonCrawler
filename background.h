// background.h
#pragma once
#include "tile.h"
#include <vector>
#include <algorithm>

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
    void CreateValidTile(Vector2 position, std::vector<Tile> previousTiles) {
        
    }

    void Generate() {
        std::vector<Vector2> occupiedPositions = {};

        Tile startingTile(0, {0, 0});
        tiles.push_back(startingTile);
        occupiedPositions.push_back(startingTile.position);

        std::vector<Tile> previousTiles = {startingTile};
        std::vector<Tile> currentTiles = {};

        bool isStillGenerating = true;
        while(isStillGenerating) {
            currentTiles = {};
            for(const Tile& i : previousTiles) {
                if(std::find(occupiedPositions.begin(), occupiedPositions.end(), Vector2{i.position.x, i.position.y-1}) != occupiedPositions.end()) {
                    // Generate tile above
                }
                if(std::find(occupiedPositions.begin(), occupiedPositions.end(), Vector2{i.position.x+1, i.position.y}) != occupiedPositions.end()) {
                    // Generate tile to right
                }
                if(std::find(occupiedPositions.begin(), occupiedPositions.end(), Vector2{i.position.x, i.position.y+1}) != occupiedPositions.end()) {
                    // Generate tile below
                }
                if(std::find(occupiedPositions.begin(), occupiedPositions.end(), Vector2{i.position.x-1, i.position.y}) != occupiedPositions.end()) {
                    // Generate tile to left
                }
            }
        }
    }
};
