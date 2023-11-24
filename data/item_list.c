#include "item_list.h"

#include <string.h>
#include "../character/item.h"
#include "../utils/memory_utils.h"
#include "../utils/string_utils.h"

// create static array of items
struct Item *items[11];

// create items
void load_item_list()
{
    items[0] = create_item("Longsword", "A longsword", 3, 15, WEAPON);
    items[1] = create_item("Shortsword", "A shortsword", 2, 10, WEAPON);
    items[2] = create_item("Dagger", "A dagger", 1, 5, WEAPON);
    items[3] = create_item("Leather Armor", "Leather armor", 5, 10, CHEST);
    items[4] = create_item("Chainmail", "Chainmail", 10, 50, CHEST);
    items[5] = create_item("Potion of Healing", "A potion of healing", 1, 25, POTION);
    items[6] = create_item("Potion of Greater Healing", "A potion of greater healing", 1, 50, POTION);
    items[7] = create_item("Potion of Fire Breath", "A potion of fire breath", 1, 100, POTION);
    items[8] = create_item("Potion of Invisibility", "A potion of invisibility", 1, 100, POTION);
    items[9] = create_item("Potion of Poison", "A potion of poison", 1, 100, POTION);
    items[10] = create_item("Dagga", "A dagga", 1, 50, WEAPON);
}

// destroy items
void destroy_items()
{
    if (items == NULL)
    {
        return;
    }

    int count = sizeof(items) / sizeof(items[0]);
    for (int i = 0; i < count; i++)
    {
        destroy_item(items[i]);
    }
}

void list_items()
{
    int count = sizeof(items) / sizeof(items[0]);
    for (int i = 0; i < count; i++)
    {
        printf("%s\n", items[i]->name);
    }
}

struct Item *get_item_by_name(char *search)
{
    struct Item *result = NULL;
    char *search_lower = toLowerCaseCopy(search);
    int count = sizeof(items) / sizeof(items[0]);
    for (int i = 0; i < count; i++)
    {
        // compare the item name to the name passed in, ignoring case
        char *item_name_lower = toLowerCaseCopy(items[i]->name);

        if (strcmp(item_name_lower, search_lower) == 0)
        {
            result = items[i];
        }

        // tidy up and maybe break the loop
        free(item_name_lower);
        if (result != NULL)
        {
            break;
        }
    }

    free(search_lower);

    return result;
}