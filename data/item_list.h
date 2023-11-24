
#ifndef ITEM_LIST_H
#define ITEM_LIST_H

#include "../character/item.h"

extern struct Item* items[];

// Function declarations
void load_item_list();
void destroy_items();
void list_items();
struct Item* get_item_by_name(char* search);

#endif // ITEM_LIST_H
