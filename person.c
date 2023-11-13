// person.c

#include "person.h"
#include <stdlib.h>
#include <string.h>

#include "utils/memory_utils.h"

// Declare initializePerson as static
static void initializePerson(struct Person *person) {
    // Default values
    strcpy(person->name, "Unknown");
    person->age = 0;
}



// Function to create a new Person
struct Person *createPerson() {
    // Allocate memory for a new Person using safeMalloc
    struct Person *newPerson = (struct Person *)safeMalloc(sizeof(struct Person));

    // Initialize the new Person
    initializePerson(newPerson);

    // Return the pointer to the new Person (or NULL if allocation failed)
    return newPerson;
}
