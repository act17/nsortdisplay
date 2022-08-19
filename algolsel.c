#include <ncurses.h>
#include <stdlib.h>
#include <pthread.h>

char algorithm[2][22] = {"Bubble Sort","Quick Sort"};

int algolsel(int prvalgol){

  int mY,mX;
  getmaxyx(stdscr,mY,mX);

  WINDOW * main = newwin(34,92,(mY - 34) / 2,(mX - 92) / 2);
  init_pair(1,COLOR_CYAN,COLOR_CYAN);
  init_pair(2,COLOR_BLACK,COLOR_WHITE);
  init_pair(3,COLOR_RED,COLOR_WHITE);
  
  box(main,0,0);
  wbkgd(stdscr,COLOR_PAIR(1));
  wbkgd(main,COLOR_PAIR(2));
  wattron(main,COLOR_PAIR(2));

  keypad(main,true);

  mvwprintw(main,2,36,"Choose Algorithm:");

  refresh();
  wrefresh(main);
  
  int choice;
  int highlight = 0;

  while(1){
    for(int i = 0; i < 2; i++){
      if(i == prvalgol)
	wattron(main,COLOR_PAIR(3));
      if(i == highlight)
        wattron(main,A_REVERSE);
      mvwprintw(main,i+4,10,"%s",algorithm[i]);
      wattroff(main,A_REVERSE);
      wattron(main,COLOR_PAIR(2));
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
        if(highlight == 1)
	  break;
	highlight++;
	break;

      default:
        break;
    }
    
    if(choice == 10 && highlight != prvalgol)
      break;
    
  }
  
  return highlight;
}
