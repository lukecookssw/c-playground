#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../character/player_character.h"
#include "../utils/save_utils.h"
#include "../utils/string_utils.h"
#include "../data/item_list.h"
#include "command_map.h"

void handle_list(struct PlayerCharacter **pc)
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
void handle_save(struct PlayerCharacter **pc)
{
    quicksave_character(pc);
}

void handle_exit(struct PlayerCharacter **pc)
{
    save_character(pc);
    exit(0);
}

void handle_attributes(struct PlayerCharacter **pc)
{

    printf("Strength:       %d\n", (*pc)->strength.attr_val);
    printf("Dexterity:      %d\n", (*pc)->dexterity.attr_val);
    printf("Constitution:   %d\n", (*pc)->constitution.attr_val);
    printf("Intelligence:   %d\n", (*pc)->intelligence.attr_val);
    printf("Wisdom:         %d\n", (*pc)->wisdom.attr_val);
    printf("Charisma:       %d\n", (*pc)->charisma.attr_val);
}

void handle_remove_item(struct PlayerCharacter **pc)
{
    // get the item name
    char item_name[32];
    printf("Item name: ");
    fgets(item_name, 32, stdin);
    strip_newline_end(item_name);

    // copy the item into the player character's inventory
    remove_item_from_inventory(pc, item_name);

    printf("%s removed.\n", item_name);
}

void handle_add_item(struct PlayerCharacter **pc)
{
    // get the item name
    char item_name[32];
    printf("Item name: ");
    fgets(item_name, 32, stdin);
    strip_newline_end(item_name);

    // look up item in item_list
    struct Item *item = get_item_by_name(item_name);
    if (item == NULL)
    {
        printf("Item not found\n");
        return;
    }

    // copy the item into the player character's inventory
    add_item_to_inventory(pc, item);

    printf("1 %s added to inventory!\n", item->name);
}

void handle_clear(struct PlayerCharacter **pc)
{
    // clear the screen
    system("clear");
    handle_print(pc);
}

void handle_print(struct PlayerCharacter **pc)
{
    print_character(pc);
}

void handle_list_items(struct PlayerCharacter **pc)
{
    list_items();
}

void handle_load_character(struct PlayerCharacter **pc)
{
    // get the character name
    char character_name[32];
    printf("Character name: ");
    fgets(character_name, 32, stdin);
    strip_newline_end(character_name);
    toLowerCase(character_name);

    // get the file
    FILE *fp = load_file(character_name);
    if (fp == NULL)
    {
        printf("No save file found with name %s\n", character_name);
        return;
    }

    // create the character
    (*pc) = load_character(character_name, fp);
    
    // close the file
    fclose(fp);
}

void request_attr(char *attr_name, unsigned short *attr_val)
{
    int minVal = 6;
    int maxVal = 18;
    printf("What is your character's %s score? ", attr_name);
    while (scanf("%d", attr_val) != 1 || *attr_val < minVal || *attr_val > maxVal)
    {
        while (getchar() != '\n')
            ; // clear the input buffer
        printf("Invalid input. Enter a number between %d and %d: ", minVal, maxVal);
    }
    while (getchar() != '\n')
        ; // consume the newline character left by scanf
}

void handle_new_character(struct PlayerCharacter **pc)
{
    // get the character name
    char character_name[32];
    fgets(character_name, 32, stdin);
    strip_newline_end(character_name);
    toUpperCase(character_name);

    // get the attributes
    unsigned short attr_val[6];
    request_attr("strength", &attr_val[0]);
    request_attr("dexterity", &attr_val[1]);
    request_attr("constitution", &attr_val[2]);
    request_attr("intelligence", &attr_val[3]);
    request_attr("wisdom", &attr_val[4]);
    request_attr("charisma", &attr_val[5]);

    // create the character
    (*pc) = new_player_character(character_name, attr_val);
}

// Define the command handlers
CommandHandler command_handlers[] = {
    {"add item", handle_add_item},
    {"remove item", handle_remove_item},
    {"clear", handle_clear},
    {"print", handle_print},
    {"list", handle_list},
    {"list items", handle_list_items},
    {"save", handle_save},
    {"load", handle_load_character},
    {"new", handle_new_character},
    {"stats", handle_attributes},
    {"attributes", handle_attributes},
    {"exit", handle_exit},
    {NULL, NULL}};