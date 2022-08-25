#include <ncurses.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include "sorts.h"

char algchr[2][22] = {"Bubble Sort","Quick Sort"};
int sortedarray[10] = {1,2,3,4,5,6,7,8,9,10};
int array[10] = {4,8,2,5,7,10,3,6,1,9};

//This is used to pass information into a pThread.
struct argumentstruct{
  int delay;
  int* array;
};
  
void ncomp(int algol,int delay){

  //This is preparing the data to be passed into a pThread:
  struct argumentstruct args;
  void* arrayvoid = &array;
  int* arraypoint = (int*)arrayvoid;
  args.array = arraypoint;
  args.delay = delay;

  //This is getting the Nanosleep-related stuff ready:
  struct timespec ts;
  ts.tv_sec = 0;
  ts.tv_nsec = delay;

  //NCurses Init
  int mX,mY,relstartX,relstartY,arraystartX,arraystartY;
  getmaxyx(stdscr,mY,mX);
  //These are the relative starts of the four windows used for flair and information display.
  relstartY = (mY - 34) / 2;
  relstartX = (mX - 92) / 2;
  //These are the relative starts of the 10 windows used to represent the array that's being sorted.
  arraystartY = relstartY + 13;
  arraystartX = relstartX + 24;	//Currently not perfectly centered.
  
  WINDOW * lborder = newwin(34,2,relstartY,relstartX);
  WINDOW * rborder = newwin(34,2,relstartY,relstartX + 92);
  WINDOW * tborder = newwin(2,90,relstartY,relstartX + 2);
  WINDOW * bborder = newwin(20,90,relstartY + 14,relstartX + 2);

  init_pair(1,COLOR_CYAN,COLOR_CYAN);
  init_pair(2,COLOR_BLACK,COLOR_WHITE);
  init_pair(3,COLOR_GREEN,COLOR_GREEN);

  box(lborder,0,0);	box(rborder,0,0);
  box(tborder,0,0);	box(bborder,0,0);

  wbkgd(stdscr,COLOR_PAIR(1));
  wbkgd(lborder,COLOR_PAIR(2));  wbkgd(rborder,COLOR_PAIR(2));
  wbkgd(tborder,COLOR_PAIR(2));  wbkgd(bborder,COLOR_PAIR(2));

  wattron(lborder,COLOR_PAIR(2));
  wattron(rborder,COLOR_PAIR(2));
  wattron(tborder,COLOR_PAIR(2));
  wattron(bborder,COLOR_PAIR(2));
  
  refresh();

  //Printing Relevant Info
  mvwprintw(bborder,1,1,"Algorithm:	%s",algchr[algol]);
  mvwprintw(bborder,2,1,"Starting Array:");
  for(int i = 0; i < 10; i++)
    mvwprintw(bborder,3,3 + 3 * i,"%d",array[i]);
  mvwprintw(bborder,4,1,"Delay:		%d ns",delay);
  mvwprintw(bborder,6,34,"PRESS ANY KEY TO BEGIN");
  
  //Array-Window creation routine.
  WINDOW * arraywin[10];
  for(int i = 0; i < 10; i++){
    arraywin[i] = newwin(array[i],4,arraystartY - array[i],arraystartX + 5 * i);
    wbkgd(arraywin[i],COLOR_PAIR(2));
    wrefresh(arraywin[i]);
  }

  wrefresh(lborder);  wrefresh(rborder);
  wrefresh(tborder);  wrefresh(bborder);

  getch();

  //pThread Init
  pthread_t thread;
  switch(algol){
  case 0:
    pthread_create(&thread,NULL,bubblewrap,&args);
    break;
  case 1:
    pthread_create(&thread,NULL,quickwrap,&args);
    break;
  default:
    pthread_create(&thread,NULL,bubblewrap,&args);
    break;
  }
  
  //Array-Window restructuring routine.
  while(1){
    //This changes the windows based on the array:
    for(int i = 0; i < 10; i++){
      wbkgd(arraywin[i],COLOR_PAIR(1));
      wrefresh(arraywin[i]);
      wresize(arraywin[i],array[i],4);
      mvwin(arraywin[i],arraystartY - array[i],arraystartX + 5 * i);
      if(array[i] == sortedarray[i])
        wbkgd(arraywin[i],COLOR_PAIR(3));
      else
        wbkgd(arraywin[i],COLOR_PAIR(2));
      wrefresh(arraywin[i]);
    }
    nanosleep(&ts,&ts);
  }
  
  getch();

  return;
}
