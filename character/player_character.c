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
    // malloc another block in the ptr_inventory for new item
    int count = player_inventory_count(pc);
    count++;
    pc->ptr_inventory = safe_realloc(pc->ptr_inventory, sizeof(struct Item) * count);

    // add the item to the inventory
    pc->ptr_inventory[count - 1] = *item;

    // loop through the inventory and print the items
    for (int i = 0; i < count; i++)
    {
        printf("%s - %dgp\n", pc->ptr_inventory[i].name, pc->ptr_inventory[i].value);
    
    }
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
}