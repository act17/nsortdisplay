#include <ncurses.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

char version[12] = "Alpha 0.2.1";
char date[9] = "19/08/22";
int begincheck = 0;

void* inputcheck(){
  getch();
  begincheck++;
  return 0;
}

void menu(){

  int mY,mX;
  getmaxyx(stdscr,mY,mX);
  
  WINDOW * main = newwin(34,92,(mY - 34) / 2,(mX - 92) / 2);
  init_pair(1,COLOR_CYAN,COLOR_CYAN);
  init_pair(2,COLOR_BLACK,COLOR_WHITE);

  box(main,0,0);
  wbkgd(stdscr,COLOR_PAIR(1));
  wbkgd(main,COLOR_PAIR(2));
  wattron(main,COLOR_PAIR(2));
  
  //Printing
  mvwprintw(main,2,38,"ACT's NCurses");
  mvwprintw(main,3,31,"Sorting Algorithm Visualiser");
  mvwprintw(main,5,41,"Version:");
  mvwprintw(main,6,40,"%s",version);
  mvwprintw(main,7,41,"%s",date);
  mvwprintw(main,9,30,"Licensed under the GNU GPL 3.0");
  mvwprintw(main,10,26,"https://github.com/act17/nsortdisplay");
  mvwprintw(main,11,36,"Copyright 2022 ACT");
  mvwprintw(main,14,34,"PRESS ANY KEY TO START");
  
  refresh();
  wrefresh(main);
  
  pthread_t inputthread;
  pthread_create(&inputthread,NULL,inputcheck,NULL);

  //The following could've been a for(); loop. But for some reason, that didn't work.
  int i = 2;
  while(1){
    if(begincheck != 0)
      break;
    
    if(i % 2 == 0)
      wattron(main,A_REVERSE);
    else
      wattroff(main,A_REVERSE);
    wrefresh(main);
    mvwprintw(main,14,34,"PRESS ANY KEY TO START");
    sleep(1);
    i++;
  }

  pthread_cancel(inputthread);

  clear();
  return;
}
