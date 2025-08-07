#pragma once
#include "character.h"
#include "item.h"
#include <vector>

class Player : public Character {
private:
    int experience; 
    int gold;

    std::vector <Item> inventory;
    //item inventory[100];
    
    

    
public:
     
    Player(int str, int sta, int itl, int dex, int team, int lvl, int weg, std::string nam , Vector2 pos, Rectangle hit = {0, 0, 0, 0}, float rot = 0.0f, float scl = 1.0f, int exper) 
     : Character(str, sta, itl, dex, team, lvl, weg, nam, pos, hit, rot, scl)
    {
        experience = exper;
    }

};