
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "save_utils.h"

#include "memory_utils.h"
#include "string_utils.h"
#include "../character/player_character.h"
#include "../data/item_list.h"

int confirm_save()
{
    char save[3]; // buffer to hold the input

    while (1)
    {
        // ask the user if they want to save
        printf("Would you like to save your character? (Y/n) ");
        fgets(save, sizeof(save), stdin);
        toUpperCase(save);

        // evaluate response
        if (save[0] == '\n' || save[0] == Y)
        {
            // Save the character
            return 1;
        }
        else if (save[0] == N)
        {
            // User entered 'y' or 'n'
            return 0;
        }
        else
        {
            // Invalid input, ask again
            printf("Invalid input. Please enter 'y' or 'n'.\n");
        }
    }
}

void write_attrs(FILE *fp, struct PlayerCharacter **pc)
{
    fprintf(fp, "%d\n", (*pc)->strength.attr_val);
    fprintf(fp, "%d\n", (*pc)->dexterity.attr_val);
    fprintf(fp, "%d\n", (*pc)->constitution.attr_val);
    fprintf(fp, "%d\n", (*pc)->intelligence.attr_val);
    fprintf(fp, "%d\n", (*pc)->wisdom.attr_val);
    fprintf(fp, "%d\n", (*pc)->charisma.attr_val);
}

void write_inventory(FILE *fp, struct PlayerCharacter **pc)
{
    if ((*pc)->ptr_inventory == NULL)
    {
        return;
    }
    // pointer arithmetic time!
    struct Item *item = (*pc)->ptr_inventory;
    /*
        Because pointer arithmetic is fucky, "item"
        can actually point beyond the length of
        the ptr_inventory array.

        We therefore need to reign in the loop
        by figuring out how many times it should iterate.

        Oh yeah, C also doesn't give us a way to track/calculate
        the size of a dynamic array, so we have to do that
        ourselves...
    */
    for (int i = 0; i < (*pc)->inventory_count; i++)
    {
        if (item->name == NULL)
        {
            break;
        }
        fprintf(fp, "%s\n", item->name);
        item++; // magical pointer arithmetic
    }
}

void quicksave_character(struct PlayerCharacter **pc)
{
    char save_dir[] = "save_files/";
    char *character_file = toLowerCaseCopy((*pc)->name);
    strip_newline_end(character_file);
    int allocSize = sizeof(save_dir) + strlen(character_file); // using sizeof() includes the null-terminator so no need for +1

    // check if there is already a file with the pc.name as the filename
    char *full_filepath = safe_malloc(allocSize);
    sprintf(full_filepath, "%s%s", save_dir, character_file);

    printf("character will be saved in %s\n", full_filepath);
    int fd = open(full_filepath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR); // open file for writing, create if it doesn't exist, truncate if it does
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    FILE *fp = fdopen(fd, "w"); // convert file descriptor to FILE*
    if (fp == NULL)
    {
        perror("fdopen");
        exit(EXIT_FAILURE);
    }
    write_attrs(fp, pc);
    write_inventory(fp, pc);
    fclose(fp);

    printf("Save successful!\n");
}

void save_character(struct PlayerCharacter **pc)
{
    int save = confirm_save();
    if (!save)
    {
        return;
    }
    quicksave_character(pc);
}

void load_inventory(FILE *fp, struct PlayerCharacter **pc)
{
    char item_name[32];
    while (fgets(item_name, sizeof(item_name), fp) != NULL)
    {
        strip_newline_end(item_name);
        // check item_name contains a value
        if (item_name[0] == '\0')
        {
            break;
        }
        struct Item *item = get_item_by_name(item_name);
        add_item_to_inventory(pc, item);
    }
}

FILE *load_file(char *file_name)
{
    char save_dir[] = "save_files/";

    // get the full file path
    int allocSize = sizeof(save_dir) + strlen(file_name);
    char *full_filepath = safe_malloc(allocSize);
    sprintf(full_filepath, "%s%s", save_dir, file_name);

    printf("Looking for %s\n", full_filepath);

    // open the file
    int fd = open(full_filepath, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        // exit(EXIT_FAILURE);
        return NULL;
    }

    FILE *fp = fdopen(fd, "r");
    if (fp == NULL)
    {
        perror("fdopen");
        return NULL;
    }

    return fp;
}

void load_attributes(FILE *fp, struct PlayerCharacter *pc)
{
    int attr_val;
    fscanf(fp, "%d", &attr_val);
    updateAttribute(&pc->strength, attr_val);

    fscanf(fp, "%d", &attr_val);
    updateAttribute(&pc->dexterity, attr_val);

    fscanf(fp, "%d", &attr_val);
    updateAttribute(&pc->constitution, attr_val);

    fscanf(fp, "%d", &attr_val);
    updateAttribute(&pc->intelligence, attr_val);

    fscanf(fp, "%d", &attr_val);
    updateAttribute(&pc->wisdom, attr_val);

    fscanf(fp, "%d", &attr_val);
    updateAttribute(&pc->charisma, attr_val);

    fgetc(fp); // consume the newline character
}

// struct PlayerCharacter *old_load_character()
// {
//     // get the character name
//     char character_file[32];
//     printf("Character name: ");
//     fgets(character_file, sizeof(character_file), stdin);
//     strip_newline_end(character_file);
//     toLowerCase(character_file); // lower case the filename

//     FILE *fp = load_file(character_file);

//     struct PlayerCharacter *pc = create_player_character(character_file);

//     load_attributes(fp, pc);

//     load_inventory(fp, pc);

//     fclose(fp);

//     return pc;
// }