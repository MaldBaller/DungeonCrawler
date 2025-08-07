#pragma once
#include "character.h"

class item {

public:

    int ID; 
    int type; //0 = can be put in main hand , 1 = can be put in second hand , 2 = top armor , 3 = chest armor , 4 = legs armor
    bool canBeStored;
    
    std::string name;
    Vector2 position;
    Rectangle hitbox;
    Texture2D texture;
    float rotation;
    float scale;
    int level;
    int weight;

    item(int id, int typ, bool canStore, std::string nam, Vector2 pos = {0, 0}, Rectangle hit = {0, 0, 0, 0}, Texture2D tex = {}, float rot = 0.0f, float scl = 1.0f, int lvl = 1, int weg = 1) {
        ID = id;
        type = typ;
        canBeStored = canStore;
        name = nam;
        position = pos;
        hitbox = hit;
        texture = tex;
        rotation = rot;
        scale = scl;
        level = lvl;
        weight = weg;
        

    }
};