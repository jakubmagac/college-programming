#define _POSIX_C_SOURCE 200201L
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>

int main(){
    srand(time(NULL));

    int world[COLS - 2*5];
    for(int i = 0; i < COLS - 2*5; i++){
        world[i] = rand() % LINES/2 + 1;
    }
    // initialize the library
    initscr();
    // set implicit modes
    cbreak();
    noecho();
    keypad(stdscr,TRUE);
    // invisible cursor, visibility of cursor (0,1,2)
    curs_set(FALSE);
    // getch() will be non-blocking
    nodelay(stdscr, TRUE);

    // your code goes here
    getchar();

    // end curses
    endwin();
}