#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include "attribute.h"
#include "item.h"

struct PlayerCharacter
{
    char name[32];
    
    // TODO: Change these to an array of attributes
    struct Attribute strength;
    struct Attribute dexterity;
    struct Attribute constitution;
    struct Attribute intelligence;
    struct Attribute wisdom;
    struct Attribute charisma;
    struct Item* ptr_inventory;
};

// functions
struct PlayerCharacter* create_player_character(char* name);
void free_player_character(struct PlayerCharacter* pc);


#endif // PLAYER_CHARACTER_H
