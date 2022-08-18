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
  int algolb = algolsel(algola);	//This macro uses the previous macro's output as a method to "grey-out" an algorithm.
  int delay = delaysel();		//This macro outputs the delay in miliseconds used in nanosleep();.
  
  //Ending routine.
  echo();
  clear();
  endwin();

  printf("\nAlgorithm 1:		%d\nAlgorithm 2:		%d",algola,algolb);
  printf("\nDelay:			%d",delay);
  
  return 0;
}
