#ifndef _SORTS_H
#define _SORTS_H

void *bubblewrap(void *args);
void *quickwrap(void *args);
void *insertionwrap(void *args);

struct argumentstruct {
  int delay;
  int *array;
  unsigned long *comp;
};

#endif
