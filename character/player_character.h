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
    struct Item *ptr_inventory;
    int inventory_count;
};

// functions
void print_character(struct PlayerCharacter *pc);
void print_character_inventory(struct PlayerCharacter *pc);
struct PlayerCharacter *create_player_character(char *name);
void free_player_character(struct PlayerCharacter *pc);
void add_item_to_inventory(struct PlayerCharacter *pc, struct Item *item);
void remove_item_from_inventory(struct PlayerCharacter *pc, char *item_name);

#endif // PLAYER_CHARACTER_H
