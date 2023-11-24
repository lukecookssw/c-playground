#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../character/player_character.h"
#include "../utils/save_utils.h"
#include "../utils/string_utils.h"
#include "../data/item_list.h"
#include "command_map.h"

void handle_list(struct PlayerCharacter* pc)
{
    // list all the command names
    int i = 0;
    printf("Available commands:\n");
    while (command_handlers[i].name != NULL)
    {
        printf("%s\n", command_handlers[i].name);
        i++;
    }
}

// Define the command handlers
void handle_save(struct PlayerCharacter* pc) {
    quicksave_character(pc);
}

void handle_exit(struct PlayerCharacter* pc) {
    save_character(pc);
    exit(0);
}

void handle_attributes(struct  PlayerCharacter* pc)
{
    
    printf("Strength:       %d\n", pc->strength.attr_val);
    printf("Dexterity:      %d\n", pc->dexterity.attr_val);
    printf("Constitution:   %d\n", pc->constitution.attr_val);
    printf("Intelligence:   %d\n", pc->intelligence.attr_val);
    printf("Wisdom:         %d\n", pc->wisdom.attr_val);
    printf("Charisma:       %d\n", pc->charisma.attr_val);
}

void handle_add_item(struct PlayerCharacter* pc)
{
    // get the item name
    char item_name[32];
    printf("Item name?");
    fgets(item_name, 32, stdin);
    strip_newline_end(item_name);

    // look up item in item_list
    struct Item* item = get_item_by_name(item_name);
    if (item == NULL)
    {
        printf("Item not found\n");
        return;
    }
    
    // copy the item into the player character's inventory
    add_item_to_inventory(pc, item);

}

void handle_print(struct PlayerCharacter* pc)
{
    print_character(pc);
}

void handle_list_items(struct PlayerCharacter* pc)
{
    list_items();
}


// Define the command handlers
CommandHandler command_handlers[] = {
    { "add item", handle_add_item },
    { "print", handle_print },
    { "list", handle_list },
    { "list items", handle_list_items },
    { "save", handle_save },
    { "stats", handle_attributes },
    { "attributes", handle_attributes },
    { "exit", handle_exit },
    { NULL, NULL }
};