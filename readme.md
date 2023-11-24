# C Keywords
| Keyword   | Description                            | Code Sample                                |
|-----------|----------------------------------------|--------------------------------------------|
| auto      | declares automatic variables           | `auto int x = 10; // declares an automatic integer variable` |
| break     | breaks out of loops                     | `for (int i = 0; i < 10; i++) { if (i == 5) break; } // breaks out of the loop when i is equal to 5` |
| case      | selects code block in switch statement | `switch (x) { case 1: printf("One"); break; case 2: printf("Two"); break; default: printf("Other"); } // selects code block based on the value of x` |
| char      | declares character variables            | `char c = 'A'; // declares a character variable` |
| const     | declares read-only variables            | `const int MAX_VALUE = 100; // declares a read-only variable` |
| continue  | skips to next iteration of loop         | `for (int i = 0; i < 10; i++) { if (i == 5) continue; printf("%d\n", i); } // skips printing 5 and continues to the next iteration` |
| default   | default code block in switch statement  | `switch (x) { case 1: printf("One"); break; case 2: printf("Two"); break; default: printf("Other"); } // executes the default code block if no other case matches` |
| do        | loops while a condition is true         | `do { printf("Hello"); } while (x < 10); // prints "Hello" while x is less than 10` |
| double    | declares double-precision variables    | `double pi = 3.14159; // declares a double-precision variable` |
| else      | executes if previous conditions fail   | `if (x > 10) { printf("Greater than 10"); } else { printf("Less than or equal to 10"); } // executes the else block if x is not greater than 10` |
| enum      | declares enumerated types               | `enum Color { RED, GREEN, BLUE }; // declares an enumerated type` |
| extern    | declares variables in another file      | `extern int x; // declares a variable defined in another file` |
| float     | declares floating-point variables       | `float f = 3.14; // declares a floating-point variable` |
| for       | loops a specific number of times        | `for (int i = 0; i < 10; i++) { printf("%d\n", i); } // loops from 0 to 9` |
| goto      | jumps to a labeled statement            | `goto label; // jumps to the statement labeled 'label'` |
| if        | executes code if a condition is true    | `if (x > 10) { printf("Greater than 10"); } // executes the code block if x is greater than 10` |
| int       | declares integer variables              | `int x = 5; // declares an integer variable` |
| long      | declares long integer variables         | `long int x = 1000000; // declares a long integer variable` |
| register  | declares register variables             | `register int x = 10; // declares a register variable` |
| return    | returns a value from a function         | `int add(int a, int b) { return a + b; } // returns the sum of a and b` |
| short     | declares short integer variables        | `short int x = 100; // declares a short integer variable` |
| signed    | declares signed variables               | `signed int x = -10; // declares a signed integer variable` |
| sizeof    | returns size of a variable in bytes     | `int size = sizeof(int); // returns the size of an integer in bytes` |
| static    | declares static variables               | `static int count = 0; // declares a static variable` |
| struct    | declares a structure type               | `struct Person { char name[20]; int age; }; // declares a structure type` |
| switch    | selects code block based on a variable  | `switch (x) { case 1: printf("One"); break; case 2: printf("Two"); break; default: printf("Other"); } // selects code block based on the value of x` |
| typedef   | creates a new type                      | `typedef int Age; // creates a new type 'Age' which is an alias for 'int'` |
| union     | declares a union type                   | `union Data { int i; float f; }; // declares a union type` |
| unsigned  | declares unsigned variables             | `unsigned int x = 10; // declares an unsigned integer variable` |
| void      | declares functions with no return value | `void printHello() { printf("Hello"); } // declares a function that prints "Hello"` |
| volatile  | declares volatile variables             | `volatile int x = 10; // declares a volatile variable` |
| while     | loops while a condition is true         | `while (x < 10) { printf("%d\n", x); x++; } // loops while x is less than 10` |
