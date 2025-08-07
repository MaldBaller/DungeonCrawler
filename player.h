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
     
    Player(int team, int lvl, std::string nam , Vector2 pos, Rectangle hit) 
     : Character(team, lvl, nam, pos, hit)
    {
        experience = 0;
    }

};