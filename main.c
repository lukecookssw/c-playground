#include <stdio.h>
#include <stdbool.h> // needed for booleans, otherwise we'd have to use 

int add(int i, int j)
{
    return i + j;
}

// C general data types: char, int, float, double


int main() {
    printf("Hello, World!\n");
    
    int i = 10;
    int j = 5;
    int k = add(i, j);
    printf("%d\n", k);
    
    return 0;
}

