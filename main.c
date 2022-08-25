#include <ncurses.h>
#include "menu.h"

int main(){

  //NCurses init routine.
  initscr();
  start_color();
  cbreak();
  noecho();
  
  //Ensures screen is not too small.
  int MaxY,MaxX;
  getmaxyx(stdscr,MaxY,MaxX);
  if(MaxY < 36 || MaxX < 94){
    printf("\n\nError!\nScreen too small!");
    printf("\nYour Y:	%d\nYour X:	%d",MaxY,MaxX);
    printf("\nMinimum:	36\n		94");
    echo();
    endwin();
    return 1;
  }

  //Macros for configuration.
  menu();
  int algola = algolsel(-1);		//This macro selects the algorithm.
  //int algolb = algolsel(algola);	//This is commented, as only doing one algorithm is possible with my current knowledge.
  int delay = delaysel();		//This macro outputs the delay in miliseconds used in nanosleep();.
  ncomp(algola,delay);			//This macro does everything relating to the actual comparing.

					//It's only going to compare one algorithm, however. It's only being kept in
					//with all the faculties of two algorithms for the sake of future addition.

  //Ending routine.
  echo();
  clear();
  endwin();
  return 0;
}
