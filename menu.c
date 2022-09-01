#include <ncurses.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

char version[12] = "Beta 1.2.1";
char date[9] = "31/08/22";
int begincheck = 0;

void *blinkdisplay() {

  int mY, mX;
  getmaxyx(stdscr, mY, mX);

  // This window is where the text will be printed. Its placement is centered at
  // line 14 on the window "main".
  WINDOW *blinkwin = newwin(1, 22, (mY - 34) / 2 + 14, (mX - 92) / 2 + 34);

  wattron(blinkwin, COLOR_PAIR(2));
  wattron(blinkwin, A_BOLD);

  while (1) {

    wattron(blinkwin, A_REVERSE);
    mvwprintw(blinkwin, 0, 0, "PRESS ANY KEY TO START");
    wrefresh(blinkwin);
    wrefresh(stdscr);
    sleep(1);
    wattroff(blinkwin, A_REVERSE);
    mvwprintw(blinkwin, 0, 0, "PRESS ANY KEY TO START");
    wrefresh(blinkwin);
    wrefresh(stdscr);
    sleep(1);
  }

  return 0;
}

void menu() {

  int mY, mX;
  getmaxyx(stdscr, mY, mX);

  WINDOW *main = newwin(34, 92, (mY - 34) / 2, (mX - 92) / 2);
  init_pair(1, COLOR_CYAN, COLOR_CYAN);
  init_pair(2, COLOR_BLACK, COLOR_WHITE);

  box(main, 0, 0);
  wbkgd(stdscr, COLOR_PAIR(1));
  wbkgd(main, COLOR_PAIR(2));
  wattron(main, COLOR_PAIR(2));

  // Printing
  mvwprintw(main, 2, 38, "ACT's NCurses");
  mvwprintw(main, 3, 31, "Sorting Algorithm Visualiser");
  mvwprintw(main, 5, 41, "Version:");
  mvwprintw(main, 6, 40, "%s", version);
  mvwprintw(main, 7, 41, "%s", date);
  mvwprintw(main, 9, 30, "Licensed under the GNU GPL 3.0");
  mvwprintw(main, 10, 26, "https://github.com/act17/nsortdisplay");
  mvwprintw(main, 11, 36, "Copyright 2022 ACT");

  refresh();
  wrefresh(main);

  pthread_t inputthread;
  pthread_create(&inputthread, NULL, blinkdisplay, NULL);

  getch();

  pthread_cancel(inputthread);

  clear();
  return;
}
