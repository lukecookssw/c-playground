
#include "item.h"

#include "../utils/memory_utils.h"
#include <string.h>

struct Item *create_item(char *name, char *description, int weight, int value, ItemSlot slot)
{
    struct Item *item = safe_malloc(sizeof(struct Item));

    strncpy(item->name, name, sizeof(item->name) - 1); // Copy name into item->name
    item->name[sizeof(item->name) - 1] = '\0';         // Ensure null termination

    strncpy(item->description, description, sizeof(item->description) - 1); // Copy description into item->description
    item->description[sizeof(item->description) - 1] = '\0';                // Ensure null termination

    item->weight = weight;
    item->value = value;
    item->equipped = 0;
    item->slot = slot;

    return item;
}

void destroy_item(struct Item *item)
{
    free(item);
}