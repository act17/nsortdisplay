#include <ncurses.h>
#include <stdlib.h>

char delayselections[3][54] = {"Slow: 500000000NS","Medium: 250000000NS","Fast: 125000000NS"};
int cmppersec[3] = {2,4,8};
char delaystring [23] = "Comparisons per Second";

int delaysel(){
  
  int mY,mX;
  getmaxyx(stdscr,mY,mX);

  WINDOW * main = newwin(34,92,(mY - 34) / 2,(mX - 92) / 2);
  init_pair(1,COLOR_CYAN,COLOR_CYAN);
  init_pair(2,COLOR_BLACK,COLOR_WHITE);

  box(main,0,0);
  wbkgd(stdscr,COLOR_PAIR(1));
  wbkgd(main,COLOR_PAIR(2));
  wattron(main,COLOR_PAIR(2));

  keypad(main,true);
  
  mvwprintw(main,2,33,"Enter/Choose the Delay:");
  
  refresh();
  wrefresh(main);

  int choice;
  int highlight = 0;

  while(1){
    for(int i = 0; i < 3; i++){
      if(i == highlight)
	wattron(main,A_REVERSE);
      mvwprintw(main,i+4,4,delayselections[i]);
      mvwprintw(main,i+4,67,"%d %s",cmppersec[i],delaystring);
      wattroff(main,A_REVERSE);
      wrefresh(main);
    }
    
    choice = wgetch(main);

    switch(choice){

      case KEY_UP:
        if(highlight == 0)
	  break;
	highlight--;
	break;
      case KEY_DOWN:
	if(highlight == 2)
	  break;
	highlight++;
      default:
        break;
    }

    if(choice == 10)
      break;

  }
  
  int delay;
  switch(highlight){
    case 0:
      delay = 500000000;
      break;
    case 1:
      delay = 250000000;
      break;
    case 2:
      delay = 125000000;
      break;
    default:
      break;
  }
  
  return delay;
}
