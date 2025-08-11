// tile.h
#include "raylib.h"

class Tile {
public:
    Texture2D tileImage;
    int tileNumber;
    Vector2 position;

    Tile(int num, Vector2 pos) {
        tileNumber = num;
        position = pos;
    }
};