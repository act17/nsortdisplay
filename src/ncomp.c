#include "sorts/sorts.h"
#include <ncurses.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// These operators are used for diagnostic and aesthetic purposes.
char algchr[3][37] = {"Bubble Sort", "Quick Sort","Insertion Sort"};
int sortedarray[18] = {1,  2,  3,  4,  5,  6,  7,  8,  9,
                       10, 11, 12, 13, 14, 15, 16, 17, 18
                      };

// This variable and function is used as a counter.
unsigned long nseccounter = 0;

void *countfunc() {
  struct timespec nsectimespec;
  nsectimespec.tv_sec = 0;
  nsectimespec.tv_nsec = 1000000;

  while (1) {
    nseccounter++;
    nanosleep(&nsectimespec, &nsectimespec);
  }

  return 0;
}

void ncomp(int algol, int delay, int *array) {

  // These operators relate to performance.
  unsigned long comparisons = 0;
  unsigned long elapsedtime = 0;

  // This is preparing the data to be passed into a pThread:
  struct argumentstruct args;
  void *arrayvoid = array;
  int *arraypoint = (int *)arrayvoid;
  args.array = arraypoint;
  args.delay = delay;
  args.comp = &comparisons;

  // This is used to check if the array is sorted.
  int sortedcheck = 0;
  int exitcheck = 0;

  // NCurses Init
  int mX, mY, relstartX, relstartY, arraystartX, arraystartY;
  getmaxyx(stdscr, mY, mX);
  // These are the relative starts of the four windows used for flair and
  // information display.
  relstartY = (mY - 34) / 2;
  relstartX = (mX - 92) / 2;
  // These are the relative starts of the 10 windows used to represent the array
  // that's being sorted.
  arraystartY = relstartY + 24;
  arraystartX = relstartX + 2; // Currently not perfectly centered.

  WINDOW *lborder = newwin(34, 2, relstartY, relstartX);
  WINDOW *rborder = newwin(34, 2, relstartY, relstartX + 92);
  WINDOW *tborder = newwin(2, 90, relstartY, relstartX + 2);
  WINDOW *bborder = newwin(10, 90, relstartY + 24, relstartX + 2);

  init_pair(1, COLOR_CYAN, COLOR_CYAN);
  init_pair(2, COLOR_BLACK, COLOR_WHITE);
  init_pair(3, COLOR_GREEN, COLOR_GREEN);

  box(lborder, 0, 0);
  box(rborder, 0, 0);
  box(tborder, 0, 0);
  box(bborder, 0, 0);

  wbkgd(stdscr, COLOR_PAIR(1));
  wbkgd(lborder, COLOR_PAIR(2));
  wbkgd(rborder, COLOR_PAIR(2));
  wbkgd(tborder, COLOR_PAIR(2));
  wbkgd(bborder, COLOR_PAIR(2));

  wattron(lborder, COLOR_PAIR(2));
  wattron(rborder, COLOR_PAIR(2));
  wattron(tborder, COLOR_PAIR(2));
  wattron(bborder, COLOR_PAIR(2));

  refresh();

  // This is getting the Nanosleep-related stuff ready:
  struct timespec ts;
  ts.tv_sec = 0;
  ts.tv_nsec = delay;

  // Printing Relevant Info
  mvwprintw(bborder, 1, 1, "Algorithm:	%s", algchr[algol]);
  mvwprintw(bborder, 2, 1, "Starting Array:");
  for (int i = 0; i < 18; i++)
    mvwprintw(bborder, 3, 3 + 3 * i, "%d", array[i]);
  mvwprintw(bborder, 4, 1, "Current Array:");
  for (int i = 0; i < 18; i++)
    mvwprintw(bborder, 5, 3 + 3 * i, "%d", array[i]);
  mvwprintw(bborder, 6, 1, "Delay:		%d ns", delay);
  mvwprintw(bborder, 7, 1, "Comparisons:	%lu", comparisons);
  mvwprintw(bborder, 8, 1, "Elapsed time:	%lu ms", elapsedtime);

  // Array-Window creation routine.
  WINDOW *arraywin[18];
  for (int i = 0; i < 18; i++) {
    arraywin[i] =
      newwin(array[i], 4, arraystartY - array[i], arraystartX + 5 * i);
    wbkgd(arraywin[i], COLOR_PAIR(2));
    wrefresh(arraywin[i]);
  }

  wrefresh(lborder);
  wrefresh(rborder);
  wrefresh(tborder);
  wrefresh(bborder);
  wrefresh(stdscr);

  getch();

  // pThread Init
  pthread_t thread;
  pthread_t counter;
  switch (algol) {
  case 0:
    pthread_create(&thread, NULL, bubblewrap, &args);
    break;
  case 1:
    pthread_create(&thread, NULL, quickwrap, &args);
    break;
  case 2:
    pthread_create(&thread, NULL, insertionwrap, &args);
    break;
  default:
    pthread_create(&thread, NULL, bubblewrap, &args);
    break;
  }
  pthread_create(&counter, NULL, countfunc, NULL);

  // Array-Window restructuring routine.
  do {

    // This changes the windows based on the array:
    for (int i = 0; i < 18; i++) {
      wbkgd(arraywin[i], COLOR_PAIR(1));
      wrefresh(arraywin[i]);
      wresize(arraywin[i], array[i], 4);
      mvwin(arraywin[i], arraystartY - array[i], arraystartX + 5 * i);
      if (array[i] == sortedarray[i])
        wbkgd(arraywin[i], COLOR_PAIR(3));
      else
        wbkgd(arraywin[i], COLOR_PAIR(2));
      wrefresh(arraywin[i]);
    }

    // Really ineffecient manner of checking if all elements are sorted:
    // This adds one for every sorted element.
    for (int i = 0; i < 18; i++) {
      if (array[i] == sortedarray[i])
        sortedcheck++;
    }

    // If the number of sorted elements is equal to the number of elements,
    // tell the program that the array is sorted.
    if (sortedcheck == 18)
      exitcheck++;
    else
      sortedcheck = 0;

    // Printing info that changes during the comparison.
    for (int i = 0; i < 18; i++)
      mvwprintw(bborder, 5, 3 + 3 * i, "%d ", array[i]);
    mvwprintw(bborder, 7, 1, "Comparisons:	%lu", comparisons);

    wrefresh(bborder);
    wrefresh(stdscr);

    nanosleep(&ts, &ts);
  } while (exitcheck == 0);

  pthread_cancel(thread);
  pthread_cancel(counter);

  // Printing diagnostics and a message to inform user that program is done
  // sorting:
  mvwprintw(bborder, 8, 1, "Elapsed time:	%lu ms", nseccounter);
  wattron(bborder, A_BOLD);
  wattron(bborder, A_REVERSE);
  mvwprintw(bborder, 7, 24, "Sorting is complete. Press any key to exit.");
  wrefresh(bborder);
  wrefresh(stdscr);
  getch();
  return;
}
