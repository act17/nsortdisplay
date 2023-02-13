#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorts.h"

void insertion(int *sorted, int size, int delay, unsigned long *comp) {

    // Getting the time-related things ready...
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = delay;

    // These two integers are used for temporary storage when swapping.
    int Temp;

    // These two loops compare each element to eachother,
    // and swaps in the case one is greater than the other.
    for(int a = 0; a < size; a++) {
        for(int b = 0; b < size; b++) {
            // We do the comparison stuff...
            nanosleep(&ts,&ts);
            *comp = *comp + 1;
            // In the case we need to swap;
            if(sorted[a] < sorted[b]) {
                Temp = sorted[a];
                sorted[a] = sorted[b];
                sorted[b] = Temp;
            }
        }
    }

    return;
}

void *insertionwrap(void* args) {
    struct argumentstruct *sortargs = args;
    insertion(sortargs->array, 18, sortargs->delay, sortargs->comp);
    return NULL;
}
