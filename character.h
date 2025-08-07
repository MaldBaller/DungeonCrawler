#pragma once
#include "raylib.h"
#include <string>

class Character {
public:
    // Basic attributes
    int health;
    int maxHealth;
    int mana;
    int maxMana;
    float speed;
    std::string name;
    Vector2 position;
    Rectangle hitbox;
    float rotation;
    float scale;
    int team; // 0 for player, 1 for enemy, 2 for neutral
    int level; // Level of the character

    /* Attributes
        Defult value is 0, every level is +1 x 3 times (ex. damage = weapon damage * strength)
        Different stats scale diffenly respect to real stats
    */
    int strength;
    int stamina;
    int intelligence;
    int dexterity;
    int weight;
    

    //character() = default;

    // Constructor
    Character(int str, int sta, int itl, int dex, int team, int lvl, int weg, std::string nam , Vector2 pos = {0, 0}, Rectangle hit = {0, 0, 0, 0}, float rot = 0.0f, float scl = 1.0f)
    {
        //level = (str + sta + itl + dex - 4) * 4; // Calculate level based on attributes
        position = pos;
        hitbox = hit;
        rotation = rot;
        scale = scl;
        name = nam;

        strength = str;
        stamina = sta;
        intelligence = itl;
        dexterity = dex;

        weight = weg;

        level = lvl;

        health = 20 + stamina * 2 + level * 1; // Base health + stamina contribution + level contribution
        maxHealth = health;

        mana = 10 + intelligence * 2 + level * 1; // Base mana + intelligence contribution + level contribution
        maxMana = mana;

        speed = 2.0f + (dexterity / 100.f) + (level / 500.f) - (weight / 3000.f); // Base speed + dexterity contribution + level contribution


    }

    void SetPosition(Vector2 pos){
        position = pos;
    }

    void Draw(){

    }
};