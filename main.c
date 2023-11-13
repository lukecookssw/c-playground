#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

// Calculate CPU usage percentage
double calculateAverage(long double *a, long double *b) {
    return ((b[0] + b[1] + b[2]) - (a[0] + a[1] + a[2])) / ((b[0] + b[1] + b[2] + b[3]) - (a[0] + a[1] + a[2] + a[3]));
}


int kbhit() {
    struct timeval tv;
    fd_set rdfs;

    tv.tv_sec = 0;
    tv.tv_usec = 0;

    FD_ZERO(&rdfs);
    FD_SET(STDIN_FILENO, &rdfs);

    select(STDIN_FILENO + 1, &rdfs, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &rdfs);
}

int main() {
    char c;
    printf("Press any key to exit.\n");

    while (1) {
        printf("CPU Usage: %.2f%%\n", getCPUUsage());
        if (kbhit()) {
            c = getchar(); // Read a character from the console
            break;
        }
    }

    return 0;
}
