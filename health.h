#pragma once
#include "character.h"

class Bar {
public:
    int barSize = 100;
    int barDistance = 70;

    Bar(int i){
        //barSize = size;
    }

    void Draw(Vector2 pos,float max, float health){
        DrawRectangle(pos.x - (barSize / 2), pos.y + barDistance,barSize,10,WHITE);
        DrawRectangle(pos.x - (barSize / 2), pos.y + barDistance,barSize * (health * 0.01 / (max * 0.01)),10,GREEN);
        DrawRectangleLines(pos.x - (barSize / 2), pos.y + barDistance,barSize,10,BLACK);
    }

};

