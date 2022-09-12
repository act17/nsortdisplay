#include "sorts/sorts.h"
#include <ncurses.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

char algchr[2][22] = {"Bubble Sort", "Quick Sort"};
int sortedarray[18] = {1,  2,  3,  4,  5,  6,  7,  8,  9,
                       10, 11, 12, 13, 14, 15, 16, 17, 18};

// This is used to pass information into a pThread.
struct argumentstruct {
  int delay;
  int *array;
};

void ncomp(int algol, int delay, int *array) {

  // This operator relates to performance.
  unsigned long comparisons = 0; // BEHOLD, my first ever use of a long!
  unsigned long elapsedtime = 0;

  // This is preparing the data to be passed into a pThread:
  struct argumentstruct args;
  void *arrayvoid = array;
  // void *compvoid = &comparisons;
  int *arraypoint = (int *)arrayvoid;
  args.array = arraypoint;
  args.delay = delay;

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
  ts.tv_nsec = delay; // This is equal to 1 ms in nanoseconds.

  // Printing Relevant Info
  mvwprintw(bborder, 1, 1, "Algorithm:	%s", algchr[algol]);
  mvwprintw(bborder, 2, 1, "Starting Array:");
  for (int i = 0; i < 18; i++)
    mvwprintw(bborder, 3, 3 + 3 * i, "%d", array[i]);
  mvwprintw(bborder, 4, 1, "Delay:		%d ns", delay);
  mvwprintw(bborder, 5, 1, "Comparisons:	%lu", comparisons);
  mvwprintw(bborder, 6, 1, "Elapsed time:	%lu ms", elapsedtime);

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
  switch (algol) {
  case 0:
    pthread_create(&thread, NULL, bubblewrap, &args);
    break;
  case 1:
    pthread_create(&thread, NULL, quickwrap, &args);
    break;
  default:
    pthread_create(&thread, NULL, bubblewrap, &args);
    break;
  }

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

    // This is for printing out the elapsed time and comparisons.
    comparisons++;
    elapsedtime = (comparisons * delay) / 1000000;
    mvwprintw(bborder, 5, 1, "Comparisons:	%lu", comparisons);  //Thanks "sbs" on the Doom Emacs Discord for this change.
    mvwprintw(bborder, 6, 1, "Elapsed time:	%lu ms", elapsedtime);

    /*
      Knowing my luck (and skill), this is probably an incorrect way of
      measuring elapsed time and comparisons. My logic on why this would work is
      that every delay, only one "if" statement in the Sorting Algorithm Thread
      is performed. As a result, that means that the number of comparisons is
      simply one per delay. Ergo, the number of comparisons can be incremented
      by one every nanosleep(); instance. As for the delays, the simple logic is
      that it's the number of delays that have occured, and those delays are
      counted with the operator "comparisons".
     */

    wrefresh(bborder);
    wrefresh(stdscr);

    nanosleep(&ts, &ts);
  } while (exitcheck == 0);

  pthread_cancel(thread);

  // Printing message to inform user that program is done sorting:
  wattron(bborder, A_BOLD);
  wattron(bborder, A_REVERSE);
  mvwprintw(bborder, 7, 24, "Sorting is complete. Press any key to exit.");
  wrefresh(bborder);
  wrefresh(stdscr);
  getch();
  return;
}
