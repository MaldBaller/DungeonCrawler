// tile.h
#pragma once
#include "raylib.h"

class Tile {
public:
    int tileNumber;
    Vector2 position;
    Rectangle collider1;
    Rectangle collider2;

    Tile(int num, Vector2 pos) {
        tileNumber = num;
        position = pos;
        if(tileNumber == 1 || tileNumber == 14) {
            collider1 = {100000,0,0,0};
            collider2 = {100000,0,0,0};
        }
        if(tileNumber == 2) {
            collider1 = {position.x*32*4 + 24*4, position.y*32*4, 8*4, 32*4};
            collider2 = {100000,0,0,0};
        }
        if(tileNumber == 3) {
            collider1 = {position.x*32*4, position.y*32*4 + 24*4, 32*4, 8*4};
            collider2 = {100000,0,0,0};
        }
        if(tileNumber == 4) {
            collider1 = {position.x*32*4, position.y*32*4, 8*4, 32*4};
            collider2 = {100000,0,0,0};
        }
        if(tileNumber == 5) {
            collider1 = {position.x*32*4, position.y*32*4, 32*4, 8*4};
            collider2 = {100000,0,0,0};
        }
        if(tileNumber == 6) {
            collider1 = {position.x*32*4, position.y*32*4, 32*4, 8*4};
            collider2 = {position.x*32*4 + 24*4, position.y*32*4, 8*4, 32*4};
        }
        if(tileNumber == 7) {
            collider1 = {position.x*32*4, position.y*32*4 + 24*4, 32*4, 8*4};
            collider2 = {position.x*32*4 + 24*4, position.y*32*4, 8*4, 32*4};
        }
        if(tileNumber == 8) {
            collider1 = {position.x*32*4, position.y*32*4 + 24*4, 32*4, 8*4};
            collider2 = {position.x*32*4, position.y*32*4, 8*4, 32*4};
        }
        if(tileNumber == 9) {
            collider1 = {position.x*32*4, position.y*32*4, 32*4, 8*4};
            collider2 = {position.x*32*4, position.y*32*4, 8*4, 32*4};
        }
        if(tileNumber == 10) {
            collider1 = {position.x*32*4 + 24*4, position.y*32*4, 8*4, 8*4};
            collider2 = {100000,0,0,0};
        }
        if(tileNumber == 11) {
            collider1 = {position.x*32*4 + 24*4, position.y*32*4 + 24*4, 8*4, 8*4};
            collider2 = {100000,0,0,0};
        }
        if(tileNumber == 12) {
            collider1 = {position.x*32*4, position.y*32*4 + 24*4, 8*4, 8*4};
            collider2 = {100000,0,0,0};
        }
        if(tileNumber == 13) {
            collider1 = {position.x*32*4, position.y*32*4, 8*4, 8*4};
            collider2 = {100000,0,0,0};
        }
    }

    void Draw(Vector2 playerPos, Texture2D* loadedTextures) {
        DrawTextureEx(loadedTextures[tileNumber], {
            float(GetScreenWidth() / 2.f - 16 * 4) + (position.x * (32*4) - playerPos.x), 
            float(GetScreenHeight() / 2.f - 16 * 4) + (position.y * (32*4) - playerPos.y)
        }, 0.f, 4.f, WHITE);
    }
};