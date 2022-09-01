#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct argumentstruct {
  int delay;
  int *array;
};

void bubble(int *array, int size, int delay) {
  struct timespec
      ts;        // NOTE TO SELF: Fix the tabbing on this file in the future.
  ts.tv_sec = 0; // This sets the delay to what the user has set.
  ts.tv_nsec = delay;
  int c = 0; // Number that represents the array entries viewed by the program.
  int currentnum, nextnum; // Used as ways to temporarily store array entries.
  for (int a = 0; a < size; a++) {
    for (int b = 1; b < size - a; b++) { // This for statement runs a routine
                                         // that moves up the highest value.

      currentnum = array[c];  // These are our compared numbers. The value of
                              // these operators changes a lot
      nextnum = array[c + 1]; // While also being imperitive to the function of
                              // the algorithim.

      nanosleep(&ts, &ts); // This is placed right before the big "if" statement
                           // that does the comparison. The reason is to create
                           // a delay before a major comparison is made.

      if (currentnum >
          nextnum) { // Next three lines can be considered the "swap routine".
        array[c] = nextnum; // This makes the current - soon to be previous -
                            // entry the lower value.
        c++;                // This increases the entry under inspection by one.
        array[c] = currentnum; // This makes the next - now the current - entry
                               // the higher value.
      }

      else { // This routine is the "pass routine".
        c++; // It simply passes the "currentnum" value to the next entry, this
             // is done via
        currentnum = array[c];
      } // not swapping.
    }

    if (a != (size - 1))
      array[c] = currentnum; // This garuntees that the set-in-stone final value
                             // of the entry is the highest. However, this skips
                             // if we're on the last number as to avoid issues.
    c = 0;                   // This resets our offset.
    printf("\n%d", array[c]);
  }
  /*for(int i = 0; i < size; i++){
          printf("\nEntry		Sorted		Original");
          printf("\n%d		%lf		%lf",i,sorted[i],array[i]);
  }*/
  return;
}

void *bubblewrap(void *args) {
  // Here's the original code for this file:
  // This creates a struct that all of our important data is "imported" into.
  struct argumentstruct *sortargs = args;
  // This tells the program to now perform bubble sort with the imported info.
  bubble(sortargs->array, 18, sortargs->delay);

  return NULL;
}
