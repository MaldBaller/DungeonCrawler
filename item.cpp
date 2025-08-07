#include "character.cpp"

class item {
private:
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

public:

    item(){

    }
}