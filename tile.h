// tile.h
#include "raylib.h"

class Tile {
public:
    Texture2D tileImage;
    int tileNumber;
    Vector2 position;

    Tile(Texture2D texture, int num, Vector2 pos) {
        tileImage = texture;
        tileNumber = num;
        position = pos;
    }
};