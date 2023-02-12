#include <ncurses.h>
#include <stdlib.h>

char delayselections[4][66] = {"Slow: 500 ms", "Medium: 250 ms", "Fast: 125 ms",
                               "Custom Delay"
                              };
int cmppersec[3] = {2, 4, 8};
char delaystring[23] = "Comparisons per Second";

int delaysel() {

    int mY, mX;
    getmaxyx(stdscr, mY, mX);

    WINDOW *main = newwin(34, 92, (mY - 34) / 2, (mX - 92) / 2);
    WINDOW *entry = newwin(2, 64, (mY - 34) / 2 + 9, (mX - 92) / 2 + 4);

    init_pair(1, COLOR_CYAN, COLOR_CYAN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_RED, COLOR_WHITE);

    box(main, 0, 0);
    wbkgd(stdscr, COLOR_PAIR(1));
    wbkgd(main, COLOR_PAIR(2));
    wbkgd(entry, COLOR_PAIR(2));
    wattron(main, COLOR_PAIR(2));
    wattron(entry, COLOR_PAIR(2));
    keypad(main, true);

    mvwprintw(main, 2, 33, "Enter/Choose the Delay:");
    // The following are controls and the "Custom Delay:", printed in bold.
    wattron(main, A_BOLD);
    wattron(entry, A_BOLD);
    mvwprintw(entry, 0, 0, "Custom Delay:      ms");
    mvwprintw(main, 31, 1, "Controls:");
    mvwprintw(main, 32, 1,
              "UP: Selection Up  DOWN: Selection Down  ENTER: Confirm Selection");
    wattroff(main, A_BOLD);
    wattroff(entry, A_BOLD);

    refresh();

    int choice;
    int highlight = 0;

    while (1) {

        for (int i = 0; i < 4; i++) {

            if (i == highlight)
                wattron(main, A_REVERSE);

            mvwprintw(main, i + 4, 4, delayselections[i]);

            if (i != 3) //"Comparisons per Second" will not be printed for the line
                // dedicated to choosing a custom delay.
                mvwprintw(main, i + 4, 64, "%d %s", cmppersec[i], delaystring);

            wattroff(main, A_REVERSE);
            wrefresh(main);
        }

        wrefresh(entry);
        wrefresh(stdscr);

        choice = wgetch(main);
        switch (choice) {

        case KEY_UP:
            if (highlight == 0)
                break;
            highlight--;
            break;

        case KEY_DOWN:
            if (highlight == 3)
                break;
            highlight++;

        default:
            break;
        }

        if (choice == 10)
            break;
    }

    int delay = 0;
    switch (highlight) {

    case 0:
        delay = 500000000;
        break;

    case 1:
        delay = 250000000;
        break;

    case 2:
        delay = 125000000;
        break;

    case 3:
        delay = 0;
        break;

    default:
        break;
    }

    if (delay == 0) { // This checks to see if the user has chosen a custom delay.

        echo();

        while (1) {

            mvwscanw(entry, 0, 15, "%d", &delay);
            mvwprintw(entry, 0, 15, "    "); // This clears the entry for delay.
            wattron(entry,
                    COLOR_PAIR(
                        3)); // This ensures the following informational text is red.
            mvwprintw(entry, 1, 23, "                          ");

            if (delay > 2147) // This is the point where the integer would overflow.
                mvwprintw(entry, 1, 0, "Error! Delay must be below 2148ms!");

            else if (delay < 0)
                mvwprintw(entry, 1, 0, "Error! Delay must be positive!");

            else if (delay == 0)
                mvwprintw(entry, 1, 0, "Error! Delay cannot be 0!");

            wrefresh(entry);
            wattron(entry, COLOR_PAIR(2));

            if (delay <= 2147 &&
                    delay > 0) // For some reason, this is the only way to make this work;
                break;       // Not do-while loop.
        }

        noecho();
        delay =
            delay *
            1000000; // This converts the delay in milliseconds(?) to nanoseconds.
    }

    clear();
    return delay;
}
