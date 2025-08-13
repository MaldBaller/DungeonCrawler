// background.h
#pragma once
#include "tile.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

// these are used to determine valid tile connections
// see "tile reference.png" to see what the numbers mean

// left first, right second
const std::vector<std::vector<int>[2]> lrConnections = {
    {{0, 1, 4, 12, 13}, {0, 1, 2, 10, 11}},
    {{0, 2, 6, 7, 14},  {0, 4, 8, 9, 14}},
    {{0, 3, 8, 11},     {0, 3, 7, 12}},
    {{0, 5, 9, 10},     {0, 5, 6, 13}}
};
// top first, bottom second
const std::vector<std::vector<int>[2]> udConnections = {
    {{0, 1, 5, 10, 13}, {0, 1, 3, 11, 12}},
    {{0, 3, 7, 8, 14},  {0, 5, 6, 9, 14}},
    {{0, 4, 9, 12},     {0, 4, 8, 13}},
    {{0, 2, 6, 11},     {0, 2, 7, 10}}
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

    Tile CreateValidTile(Vector2 position, std::vector<Tile> previousTiles) {
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
        
        // actually pick a tile!
        std::vector<int> validTiles = {};

        int valid = 0;

        //find which tiles are valid in that position
        for(int i = 1; i <= 14; i++) {
            for(const std::vector<int> j[2] : lrConnections) {
                if(std::find(j[0].begin(), j[0].end(), left) != j[0].end() && std::find(j[1].begin(), j[1].end(), i) != j[1].end()) {valid += 1}
                if(std::find(j[0].begin(), j[0].end(), i) != j[0].end() && std::find(j[1].begin(), j[1].end(), right) != j[1].end()) {valid += 1}
            }
            for(const std::vector<int> j[2] : udConnections) {
                if(std::find(j[0].begin(), j[0].end(), above) != j[0].end() && std::find(j[1].begin(), j[1].end(), i) != j[1].end()) {valid += 1}
                if(std::find(j[0].begin(), j[0].end(), i) != j[0].end() && std::find(j[1].begin(), j[1].end(), below) != j[1].end()) {valid += 1}
            }
            if(valid == 4) {
                validTiles.push_back(i);
            }
        }

        // pick a random one
        std::srand(std::time({})); // use current time as seed for random generator
        Tile finalTile(validTiles[std::rand() % validTiles.size()], position);
        return(finalTile);
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
                if(std::find(occupiedPositions.begin(), occupiedPositions.end(), Vector2{i.position.x, i.position.y-1}) != occupiedPositions.end() && i.position.y-1 > -(height/2)) {
                    currentTiles.push_back(CreateValidTile(Vector2{i.position.x, i.position.y-1}, previousTiles));
                } 
                else if(std::find(occupiedPositions.begin(), occupiedPositions.end(), Vector2{i.position.x+1, i.position.y}) != occupiedPositions.end() && i.position.x+1 < (width/2)) {
                    currentTiles.push_back(CreateValidTile(Vector2{i.position.x+1, i.position.y}, previousTiles));
                } 
                else if(std::find(occupiedPositions.begin(), occupiedPositions.end(), Vector2{i.position.x, i.position.y+1}) != occupiedPositions.end() && i.position.y+1 < (height/2)) {
                    currentTiles.push_back(CreateValidTile(Vector2{i.position.x, i.position.y+1}, previousTiles));
                } 
                else if(std::find(occupiedPositions.begin(), occupiedPositions.end(), Vector2{i.position.x-1, i.position.y}) != occupiedPositions.end() && i.position.x-1 > -(width/2)) {
                    currentTiles.push_back(CreateValidTile(Vector2{i.position.x-1, i.position.y}, previousTiles));
                }
            }

            if(currentTiles == {}) {break;}
            tiles.insert(tiles.end(), currentTiles.begin(), currentTiles.end());
        }
    }

    void Draw(Vector2 playerPos) {
        for(Tile& i : tiles) {
            i.Draw(playerPos);
        }
    }
};
