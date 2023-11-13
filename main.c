#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#include <sys/time.h>
#include <sys/types.h>


#include "utils/memory_utils.h"
#include "utils/file_utils.h"

// Function to allocate and read CPU time values from /proc/stat
long double *readCPUTime() {
    long double *cpuTime = safeMalloc(4 * sizeof(long double));
    
    FILE *fp = safefopen("/proc/stat", "r");

    // Read CPU time values into the array
    fscanf(fp, "%*s %Lf %Lf %Lf %Lf", &cpuTime[0], &cpuTime[1], &cpuTime[2], &cpuTime[3]);

    fclose(fp);

    return cpuTime;
}

// Function to free memory allocated for CPU time values
void freeCPUTime(long double *cpuTime) {
    free(cpuTime);
}
// Calculate CPU usage percentage
double calculateAverage(long double *a, long double *b) {
    return ((b[0] + b[1] + b[2]) - (a[0] + a[1] + a[2])) / ((b[0] + b[1] + b[2] + b[3]) - (a[0] + a[1] + a[2] + a[3]));
}
// Function to get current CPU usage on Linux Mint
double getCPUUsage() {
    long double *a, *b;

    // Read CPU time values before sleeping
    a = readCPUTime();

    sleep(1); // Sleep for one second

    // Read CPU time values after sleeping
    b = readCPUTime();

    // Calc average CPU usage between the 2 results
    double loadavg = calculateAverage(a, b);

    // Free the allocated memory
    freeCPUTime(a);
    freeCPUTime(b);

    return loadavg * 100.0;
}




int kbhit() {
    // Create some timeval that is used for the select(...) method
    // to make it "non-blocking"
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;

    // Create a file descriptor set because "everything in Unix is a file."
    // Even keyboard inputs. This will be used in the select(...) method
    fd_set rdfs;
    
    // Create pointers just cos we can.
    fd_set *rdfs_ptr = &rdfs;
    struct timeval *tv_ptr = &tv;

    // Clear the set using the FD_ZERO macro because 
    // it might already have something in that memory location
    FD_ZERO(rdfs_ptr); 
    
    // Set the file descriptor to the const STDIN_FILENO
    // which is the file descriptor for the standard input (e.g. keyboard)
    FD_SET(STDIN_FILENO, rdfs_ptr);

    

    // Check if there is any input from the keyboard

    select(STDIN_FILENO + 1, &rdfs, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &rdfs);
}

int main() {
    char c;
    printf("Press any key to exit.\n");


    // pointers and references, oh my!
    int* ptr;
    
    int var = 9;
    ptr = &var;
    *ptr = 10;
    
    int foo = 21;
    ptr = &foo;
    *ptr = 22;
    
    // There is no reference type like this in C (only C++)
    //int& ref = var;
    int* ref = &var; // Same thing as int* ptr
    
    printf("var: %d\n", var);
    printf("foo: %d\n", foo);
    printf("ptr: %d\n", *ptr);
    printf("ref: %d\n", *ref);

    while (1) {
        printf("CPU Usage: %.2f%%\n", getCPUUsage());
        if (kbhit()) {
            c = getchar(); // Read a character from the console
            break;
        }
    }

    

    return 0;
}
