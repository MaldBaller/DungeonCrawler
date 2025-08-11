// tile.h
#include "raylib.h"

class Tile {
public:
    Texture2D tileImage;
    Vector2 position;

    Tile(Texture2D texture, Vector2 pos) {
        tileImage = texture;
        position = pos;
    }
};