#include "sorts.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// This function partitions and sorts the array into two halves.
int qpart(int *array, unsigned long *comp, int min, int max, int delay) {
    int pivot = array[max];
    int index = min - 1; // This is the numeric value of the index which the two
    // partitions split.
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = delay;
    double temp;
    for (int i = min; i < max; i++) {

        nanosleep(
            &ts,
            &ts); // This is meant to cause a delay before a major comparison/move.
        *comp = *comp + 1;

        if (array[i] <=
                pivot) { // This routine places numbers on their correct position.
            index++;
            temp = array[i];
            array[i] = array[index];
            array[index] = temp;
        }
    }
    index++;
    temp = array[max]; // This swap is made to correct the index position.
    array[max] = array[index];
    array[index] = temp;
    return index;
}

// This function serves as a wrapper to qpart();.
void qksrt(int *array, unsigned long *comp, int min, int max, int delay) {
    if (min >= max || min < 0)
        return;
    int partition = qpart(array, comp, min, max, delay);
    qksrt(array, comp, min, partition - 1, delay);
    qksrt(array, comp, partition + 1, max, delay);
}

// This function servers as a wrapper to the wrapper qksrt();.
void *quickwrap(void *args) {
    struct argumentstruct *sortargs = args;
    qksrt(sortargs->array, sortargs->comp, 0, 17, sortargs->delay);
    return NULL;
}
