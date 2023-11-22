#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "character/attribute.h"
#include "character/player_character.h"
#include "utils/save_utils.h"
#include "utils/string_utils.h"

char Y = 'Y';
char N = 'N';

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
}

void set_attributes(struct PlayerCharacter *pc, int scores[6])
{
    updateAttribute(&pc->strength, scores[0]);
    updateAttribute(&pc->dexterity, scores[1]);
    updateAttribute(&pc->constitution, scores[2]);
    updateAttribute(&pc->intelligence, scores[3]);
    updateAttribute(&pc->wisdom, scores[4]);
    updateAttribute(&pc->charisma, scores[5]);
}

struct PlayerCharacter *create_character_form()
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
    // update the attributes
    set_attributes(pc, attrs);

    return pc;
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
}

char request_save(struct PlayerCharacter *pc)
{
    printf("Would you like to save your character? (Y/n) ");
    char save[3]; // buffer to hold the input
    fgets(save, sizeof(save), stdin);
    toUpperCase(save);
    if (save[0] == '\n')
    {
        // User just hit enter, return a default value
        return Y;
    }
    else if (save[0] == Y || save[0] == N)
    {
        // User entered 'y' or 'n'
        return save[0];
    }
    else
    {
        // Invalid input, you could ask again or return a default value
        printf("Invalid input. Please enter 'y' or 'n'.\n");
        return request_save(pc);
    }
}

char request_load()
{
    printf("Load existing character? (Y/n)");
    char load[3]; // buffer to hold the input
    fgets(load, sizeof(load), stdin);
    toUpperCase(load);
    // check that they entered either nothing, or y/n
    if (load[0] == '\n' || load[0] == Y)
    {
        return Y;
    }
    else if (load[0] == N)
    {
        return N;
    }
    else
    {
        // Invalid input, you could ask again or return a default value
        printf("Invalid input. Please enter 'y' or 'n'.\n");
        return request_load();
    }
}

void command_listener(struct PlayerCharacter *pc)
{
    char command[32];
    while (1)
    {
        printf("Enter a command: ");
        fgets(command, sizeof(command), stdin);
        // Remove newline character
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "save") == 0)
        {
            // save the character
            save_character(pc);
        }
        else if (strcmp(command, "exit") == 0)
        {
            break; // exit the loop
        }
        else
        {
            printf("Invalid command. Please enter 'save' or 'exit'.\n");
        }
    }
}



int main()
{
    struct PlayerCharacter *pc;

    char load = request_load();
    if (load == Y)
    {
        pc = load_character();
    }
    else
    {
        pc = create_character_form();
    }

    print_character(pc);

    command_listener(pc);

    // // --- OLD CODE ---
    // char save = request_save(pc);
    // if (save == Y)
    // {
    //     // save the character
    //     save_character(pc);
    // }
    return 0;
}
