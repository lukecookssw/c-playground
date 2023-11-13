// main.c
#include <stdio.h>
#include <stdlib.h>

#include "person.h"



int main() {
    // Create a new Person using createPerson
    struct Person *person1 = createPerson();

    // Using the initialized Person
    printf("Person's name: %s\n", person1->name);
    printf("Person's age: %d\n", person1->age);

    // Free the allocated memory when done
    free(person1);

    return 0;
}
