// player_character.c

#include <stdio.h>
#include <string.h>

#include "../utils/memory_utils.h"
#include "../utils/string_utils.h"
#include "../data/item_list.h"

#include "player_character.h"
#include "item.h"

// Comparison function for qsort
static int compareItems(const void *a, const void *b)
{
    return strcmp(((struct Item *)a)->name, ((struct Item *)b)->name);
}

void add_item_to_inventory(struct PlayerCharacter **pc, struct Item *item)
{
    // Increase the size of the ptr_inventory array
    int count = (*pc)->inventory_count;
    struct Item *new_ptr_inventory = safe_realloc((*pc)->ptr_inventory, sizeof(struct Item) * ((*pc)->inventory_count + 1));

    // Check if realloc was successful
    if (new_ptr_inventory == NULL)
    {
        // Handle the error...
        printf("Error: could not allocate memory for item\n");
        return;
    }

    // Update ptr_inventory with the new pointer
    (*pc)->ptr_inventory = new_ptr_inventory;

    // create a copy of the item to store in the player's inventory
    struct Item *item_copy = safe_malloc(sizeof(struct Item));
    memcpy(item_copy, item, sizeof(struct Item));

    // Copy the item into the ptr_inventory array
    (*pc)->ptr_inventory[count] = *item_copy;
    (*pc)->inventory_count++;

    // sort
    qsort(
        (*pc)->ptr_inventory,
        (*pc)->inventory_count,
        sizeof(struct Item),
        compareItems);
}

static int find_item_index(struct PlayerCharacter **pc, char *item_name)
{
    int result = -1;
    // check to see if there's any inventory at all
    if ((*pc)->ptr_inventory == NULL)
    {
        return -1;
    }
    char *item_name_lower = toLowerCaseCopy(item_name);
    // find the item in the inventory
    int i = 0;
    while ((*pc)->ptr_inventory[i].name[0] != '\0')
    {
        char *inventory_item_name_lower = toLowerCaseCopy((*pc)->ptr_inventory[i].name);
        if (strcmp(inventory_item_name_lower, item_name_lower) == 0)
        {
            result = i;
        }
        i++;

        // tidy up
        free(inventory_item_name_lower);
        if (result != -1)
        {
            break;
        }
    }
    free(item_name_lower);
    return result;
}

void remove_item_from_inventory(struct PlayerCharacter **pc, char *item_name)
{
    struct Item *inventory = (*pc)->ptr_inventory;

    // find the item in the inventory
    int i = find_item_index(pc, item_name);
    if (i == -1)
    {
        printf("No item with name %s found in inventory\n", item_name);
        return;
    }

    if ((*pc)->inventory_count == 1)
    {
        free((*pc)->ptr_inventory);
        (*pc)->inventory_count = 0;
        return;
    }

    memmove(
        inventory + i,                                  // dest
        inventory + i + 1,                              // source
        sizeof(struct Item) * ((*pc)->inventory_count - i) // size
    );
    inventory = safe_realloc(inventory, sizeof(struct Item) * ((*pc)->inventory_count - 1));
    (*pc)->inventory_count--;
}

void free_player_character(struct PlayerCharacter **pc)
{
    // free the inventory
    free((*pc)->ptr_inventory);

    // free the character
    free((*pc));
}

static struct PlayerCharacter *create_player_character(char *name)
{
    // allocate the memory
    struct PlayerCharacter *pc = safe_malloc(sizeof(struct PlayerCharacter));
    pc->inventory_count = 0;

    // set the name
    strcpy(pc->name, toUpperCaseCopy(name));

    return pc;
}

void print_character_inventory(struct PlayerCharacter **pc)
{
    printf("-------------------Inventory---------------------\n");
    printf("Name                           | Weight | Value  \n");
    if ((*pc)->ptr_inventory == NULL)
    {
        printf("Empty :(\n");
        return;
    }
    int i = 0;
    while ((*pc)->ptr_inventory[i].name[0] != '\0')
    {
        printf("%-30s | %-6d | %-6d\n", (*pc)->ptr_inventory[i].name, (*pc)->ptr_inventory[i].weight, (*pc)->ptr_inventory[i].value);
        i++;
    }
    printf("-------------------------------------------------\n");
}

void print_character(struct PlayerCharacter **pc)
{
    printf("-------------------------------------------------\n");
    printf("Name: %s\n\n", (*pc)->name);
    printf("Attribute\tScore\tModifier\n");
    printf("Strength\t%d\t%c%d\n", (*pc)->strength.attr_val, (*pc)->strength.attr_mod >= 0 ? '+' : '-', abs((*pc)->strength.attr_mod));
    printf("Dexterity\t%d\t%c%d\n", (*pc)->dexterity.attr_val, (*pc)->dexterity.attr_mod >= 0 ? '+' : '-', abs((*pc)->dexterity.attr_mod));
    printf("Constitution\t%d\t%c%d\n", (*pc)->constitution.attr_val, (*pc)->constitution.attr_mod >= 0 ? '+' : '-', abs((*pc)->constitution.attr_mod));
    printf("Intelligence\t%d\t%c%d\n", (*pc)->intelligence.attr_val, (*pc)->intelligence.attr_mod >= 0 ? '+' : '-', abs((*pc)->intelligence.attr_mod));
    printf("Wisdom\t\t%d\t%c%d\n", (*pc)->wisdom.attr_val, (*pc)->wisdom.attr_mod >= 0 ? '+' : '-', abs((*pc)->wisdom.attr_mod));
    printf("Charisma\t%d\t%c%d\n", (*pc)->charisma.attr_val, (*pc)->charisma.attr_mod >= 0 ? '+' : '-', abs((*pc)->charisma.attr_mod));

    print_character_inventory(pc);
}

struct PlayerCharacter *load_character(char *character_name, FILE *fp)
{
    // create the character
    struct PlayerCharacter *pc = create_player_character(character_name);

    // read through the attributes, lines 1-6
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

    // read through the inventory and add items
    char item_name[32];

    int ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            continue;
        }

        ungetc(ch, fp);

        if (fscanf(fp, "%31[^\n] ", item_name) != 1)
        {
            break;
        }

        struct Item *item = get_item_by_name(item_name);
        if (item == NULL)
        {
            printf("Item not found: %s\n", item_name);
            continue;
        }

        add_item_to_inventory(&pc, item);
    }

    return pc;
}

struct PlayerCharacter *new_player_character(char *name, unsigned short *attributes)
{
    struct PlayerCharacter *pc = create_player_character(name);
    updateAttribute(&pc->strength, attributes[0]);
    updateAttribute(&pc->dexterity, attributes[1]);
    updateAttribute(&pc->constitution, attributes[2]);
    updateAttribute(&pc->intelligence, attributes[3]);
    updateAttribute(&pc->wisdom, attributes[4]);
    updateAttribute(&pc->charisma, attributes[5]);
    return pc;
}