// person.h

#ifndef PERSON_H
#define PERSON_H

struct Person {
    char name[50];
    int age;
};

// Function declarations
struct Person *createPerson();

#endif // PERSON_H
