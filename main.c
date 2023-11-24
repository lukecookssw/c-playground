#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "character/attribute.h"
#include "character/player_character.h"
#include "utils/save_utils.h"
#include "utils/string_utils.h"
#include "commands/command_map.h"
#include "data/item_list.h"


void request_attr(char *attr_name, int *attr_val)
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

struct PlayerCharacter *new_character()
{
    // ask the user to type in their character's name
    char name[32];
    printf("What is your character's name? ");
    fgets(name, sizeof(name), stdin);

    // get the attribute scores
    int attrs[6];
    request_attr("strength", &attrs[0]);
    request_attr("dexterity", &attrs[1]);
    request_attr("constitution", &attrs[2]);
    request_attr("intelligence", &attrs[3]);
    request_attr("wisdom", &attrs[4]);
    request_attr("charisma", &attrs[5]);

    // create the player character
    struct PlayerCharacter *pc = create_player_character(name);

    // set the attributes
    updateAttribute(&pc->strength, attrs[0]);
    updateAttribute(&pc->dexterity, attrs[1]);
    updateAttribute(&pc->constitution, attrs[2]);
    updateAttribute(&pc->intelligence, attrs[3]);
    updateAttribute(&pc->wisdom, attrs[4]);
    updateAttribute(&pc->charisma, attrs[5]);

    return pc;
}



int request_load()
{
    char load[3]; // buffer to hold the input

    while (1)
    {
        printf("Load existing character? (Y/n)");
        fgets(load, sizeof(load), stdin);
        toUpperCase(load);

        // check that they entered either nothing, or y/n
        if (load[0] == '\n' || load[0] == Y)
        {
            return 1;
        }
        else if (load[0] == N)
        {
            return 0;
        }
        else
        {
            // Invalid input, ask again
            printf("Invalid input. Please enter 'y' or 'n'.\n");
        }
    }
}

void command_listener(struct PlayerCharacter *pc)
{
    char command[32];

    while (1)
    {
        printf("Enter a command: ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';

        int i = 0;
        while (command_handlers[i].name != NULL)
        {
            if (strcmp(command, command_handlers[i].name) == 0)
            {
                command_handlers[i].handler(pc);
                break;
            }
            i++;
        }

        if (command_handlers[i].name == NULL)
        {
            printf("Invalid command. Please enter a valid command.\n");
        }
    }
}

void load_data()
{
    // load the item list
    load_item_list();
}

struct PlayerCharacter *initialize_session()
{
    struct PlayerCharacter *pc;
    int load = request_load();
    if (load)
    {
        pc = load_character();
    }
    else
    {
        pc = new_character();
    }

    return pc;
}

int main()
{
    load_data();
    struct PlayerCharacter *pc = initialize_session();
    print_character(pc);
    command_listener(pc);

    return 0;
}
