// background.h
#pragma once
#include "tile.h"
#include <vector>
#include <algorithm>

// these are used to determine valid tile connections
// left first, right second
const std::vector<std::vector<int>[2]> lrConnections = {
    {{1, 4, 12, 13}, {1, 2, 10, 11}},
    {{2, 6, 7, 14}, {4, 8, 9, 14}},
    {{3, 8, 11}, {3, 7, 12}},
    {{5, 9, 10}, {5, 6, 13}}
};
// top first, bottom second
const std::vector<std::vector<int>[2]> udConnections = {
    {{1, 5, 10, 13}, {1, 3, 11, 12}},
    {{3, 7, 8, 14}, {5, 6, 9, 14}},
    {{4, 9, 12}, {4, 8, 13}},
    {{2, 6, 11}, {2, 7, 10}}
};

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
        // find any adjacent tiles (0 means no tile)
        int above=0, right=0, below=0, left=0;

        for(const Tile& i : previousTiles) {
            if(i.position.x == position.x && i.position.y == position.y-1) {
                above = i.tileNumber;
            } else if(i.position.x == position.x+1 && i.position.y == position.y) {
                right = i.tileNumber;
            } else if(i.position.x == position.x && i.position.y == position.y+1) {
                below = i.tileNumber;
            } else if(i.position.x == position.x-1 && i.position.y == position.y) {
                left = i.tileNumber;
            }
        }
        // create one that fits all
    }

    void Generate() {
        std::vector<Vector2> occupiedPositions = {};

        // start on an empty tile in the middle
        Tile startingTile(1, {0, 0});
        tiles.push_back(startingTile);
        occupiedPositions.push_back(startingTile.position);

        std::vector<Tile> previousTiles = {startingTile};
        std::vector<Tile> currentTiles = {};

        //repeatedly generate tiles in adjacent positions
        bool isStillGenerating = true;
        while(isStillGenerating) {
            currentTiles = {};
            for(const Tile& i : previousTiles) {
                if(std::find(occupiedPositions.begin(), occupiedPositions.end(), Vector2{i.position.x, i.position.y-1}) != occupiedPositions.end()) {
                    // Generate tile above
                } else if(std::find(occupiedPositions.begin(), occupiedPositions.end(), Vector2{i.position.x+1, i.position.y}) != occupiedPositions.end()) {
                    // Generate tile to right
                } else if(std::find(occupiedPositions.begin(), occupiedPositions.end(), Vector2{i.position.x, i.position.y+1}) != occupiedPositions.end()) {
                    // Generate tile below
                } else if(std::find(occupiedPositions.begin(), occupiedPositions.end(), Vector2{i.position.x-1, i.position.y}) != occupiedPositions.end()) {
                    // Generate tile to left
                }
            }

            //know when to end loop
        }
    }
};
