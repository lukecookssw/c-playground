// Constant
const int c_var = 20;

// Pointer constant?!
const int* const ptr = &c_var;


// Strings are weird.
char string1[20] = {'g', 'e', 'e', 'k', 's', 'f', 'o', 'r', 'g', 'e', 'e', 'k', 's', '\0'};
char string2[20] = "geeksforgeeks";
char string3[] = "geeksforgeeks";

// Loops are normal.
void DemoLoop(int loopNumber)
{
    register char c = 's'; // magical register keyword keeps the value in the CPU register

    for (int i = 0; i < loopNumber; i++)
    {
        if (i == 5)
            break;
        
        printf("Hello World, %d\n", i);
    }
}

// Scary goto
void GotoExample() {
    int n = 1;
label:
    printf("%d ", n);
    n++;
    if (n <= 10) goto label; // why tho
}