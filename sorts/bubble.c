#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct argumentstruct {
  int delay;
  int *array;
};

void bubble(int *sorted, int size, int delay) {
  // Preparing nanosleep();
  struct timespec ts;
  ts.tv_sec = 0;
  ts.tv_nsec = delay;

  int offset = 0;       // This is an offset that the program uses when scanning
                        // through entries.
  double current, next; // This is temporary storage for numbers when swapping.

  for (int a = 0; a < size;
       a++) { // This loop repeats until the array is garunteed to be sorted.

    for (int b = 1; b < size - a; b++) { // This loop repeats until an entry has
                                         // reached its garunteed proper place.

      current = sorted[offset];
      next = sorted[offset + 1];

      nanosleep(&ts, &ts); // This is to delay the program's comparison.

      if (current > next) { // This occurs when the two entries must be swapped.
        sorted[offset] = next;
        offset++;
        sorted[offset] = current;
      }

      else // This occurs when the opposite is true, and the offest - which is
           // the next highest
        offset++; // number just by the way - is the next entry in the array.
    }

    if (a != (size - 1)) // This is an error prevention measure that ensures our
                         // final value is what it must be.
      sorted[offset] = current;

    offset = 0;
  }

  return;
}

void *bubblewrap(void *args) {
  struct argumentstruct *sortargs = args;
  bubble(sortargs->array, 17, sortargs->delay);
  return NULL;
}
