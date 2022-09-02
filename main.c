#include "menu.h"
#include <ncurses.h>

int main() {
  int array[18] = {1,18,2,17,3,16,4,15,5,14,6,13,7,12,8,11,9,10};
  // NCurses init routine.
  initscr();
  start_color();
  cbreak();
  noecho();

  // Ensures screen is not too small.
  int MaxY, MaxX;
  getmaxyx(stdscr, MaxY, MaxX);

  if (MaxY < 36 || MaxX < 94) {

    printf("\n\nError!\nScreen too small!");
    printf("\nYour Y:	%d\nYour X:	%d", MaxY, MaxX);
    printf("\nMinimum:	36\n		94");
    echo();
    endwin();
    return 1;
  }

  // Macros for configuration.
  menu();
  int algola = algolsel(-1); // This macro selects the algorithm.
  // int algolb = algolsel(algola);	//This is commented, as only doing one
  					//algorithm is possible with my current knowledge.
  int delay = delaysel(); // This macro outputs the delay in miliseconds used in
                          // nanosleep();.
  ncomp(algola,
        delay,
	array); // This macro does everything relating to the actual comparing.

  // It's only going to compare one algorithm, however. It's only being kept in
  // with all the faculties of two algorithms for the sake of future addition.

  // Ending routine.
  echo();
  clear();
  endwin();
  return 0;
}
