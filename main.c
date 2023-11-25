#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "character/attribute.h"
#include "character/player_character.h"
#include "utils/save_utils.h"
#include "utils/string_utils.h"
#include "commands/command_map.h"
#include "data/item_list.h"

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

            // clear the buffer
            while (getchar() != '\n')
                ;
        }
    }
}

void command_listener(struct PlayerCharacter **pc)
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
            // clear the buffer
            while (getchar() != '\n')
                ;
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
        handle_load_character(&pc);
    }
    else
    {
        handle_new_character(&pc);
    }
    return pc;
}

int main()
{
    load_data();
    struct PlayerCharacter *pc = initialize_session();
    print_character(&pc);
    command_listener(&pc);

    return 0;
}