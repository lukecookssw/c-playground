// player_character.c

#include <string.h>

#include "../utils/memory_utils.h"
#include "../utils/string_utils.h"

#include "player_character.h"
#include "item.h"


static int player_inventory_count(struct  PlayerCharacter *pc)
{
    // check to see if there's any inventory at all
    if (pc->ptr_inventory == NULL)
    {
        return 0;
    }

    int count = 0;
    while (pc->ptr_inventory[count].name[0] != '\0')
    {
        count++;
    }
    return count;
}

void add_item_to_inventory(struct PlayerCharacter* pc, struct Item* item)
{
    // Increase the size of the ptr_inventory array
    int count = player_inventory_count(pc);
    struct Item* new_ptr_inventory = realloc(pc->ptr_inventory, sizeof(struct Item) * (count + 1));
    
    // Check if realloc was successful
    if (new_ptr_inventory == NULL)
    {
        // Handle the error...
        printf("Error: could not allocate memory for item\n");
        return;
    }

    // Update ptr_inventory with the new pointer
    pc->ptr_inventory = new_ptr_inventory;

    // create a copy of the item to store in the player's inventory
    struct Item* item_copy = safe_malloc(sizeof(struct Item));
    memcpy(item_copy, item, sizeof(struct Item));

    // Copy the item into the ptr_inventory array
    pc->ptr_inventory[count] = *item_copy;
}



void free_player_character(struct PlayerCharacter* pc)
{
    // free the inventory
    free(pc->ptr_inventory);

    // free the character
    free(pc);
}

struct PlayerCharacter* create_player_character(char* name)
{
    // allocate the memory
    struct PlayerCharacter* pc = safe_malloc(sizeof(struct PlayerCharacter));
    
    // set the name
    strcpy(pc->name, toUpperCaseCopy(name));

    struct Item* default_item = create_item("default item", "this is a default item", 1, 1, NO_SLOT);
    // add a single default item to the inventory
    add_item_to_inventory(pc, default_item);

    return pc;
}

void print_character_inventory(struct PlayerCharacter *pc)
{
    printf("-------------------Inventory---------------------\n");
    printf("Name                           | Weight | Value |\n");
    if (pc->ptr_inventory == NULL)
    {
        printf("Empty :(\n");
        return;
    }
    int i = 0;
    while (pc->ptr_inventory[i].name[0] != '\0')
    {
        printf("%-30s | %-6d | %-6d\n", pc->ptr_inventory[i].name, pc->ptr_inventory[i].weight, pc->ptr_inventory[i].value);
        i++;
    }
    printf("-------------------------------------------------\n");
}

void print_character(struct PlayerCharacter *pc)
{
    printf("Name: %s\n", pc->name);
    printf("Attribute\tScore\tModifier\n");
    printf("Strength\t%d\t%c%d\n", pc->strength.attr_val, pc->strength.attr_mod >= 0 ? '+' : '-', abs(pc->strength.attr_mod));
    printf("Dexterity\t%d\t%c%d\n", pc->dexterity.attr_val, pc->dexterity.attr_mod >= 0 ? '+' : '-', abs(pc->dexterity.attr_mod));
    printf("Constitution\t%d\t%c%d\n", pc->constitution.attr_val, pc->constitution.attr_mod >= 0 ? '+' : '-', abs(pc->constitution.attr_mod));
    printf("Intelligence\t%d\t%c%d\n", pc->intelligence.attr_val, pc->intelligence.attr_mod >= 0 ? '+' : '-', abs(pc->intelligence.attr_mod));
    printf("Wisdom\t\t%d\t%c%d\n", pc->wisdom.attr_val, pc->wisdom.attr_mod >= 0 ? '+' : '-', abs(pc->wisdom.attr_mod));
    printf("Charisma\t%d\t%c%d\n", pc->charisma.attr_val, pc->charisma.attr_mod >= 0 ? '+' : '-', abs(pc->charisma.attr_mod));

    print_character_inventory(pc);
}
