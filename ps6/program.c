#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

void init();
void menu(int dificulty);
void si_skoncil();
void prvy_level(int dificulty);

// e, m, h
int main(int argc, char *argv[])
{
    int dificulty = 100000;
    //if(argv[0] == 'e') dificulty = 100000;
    //if(argv[0] == 'm') dificulty = 50000;
    //if(argv[0] == 'h') dificulty = 10000;

    init();
    menu(dificulty);
    endwin();
    return 0;
}
void prvy_level(int dificulty)
{
    clear();
    char ch;
    FILE *maze1 = fopen("maze1.txt", "r");
    refresh();
    char maze[84][30];
    int i=0; int s = 0;


    while(ch!=EOF)
    {
        ch = fgetc(maze1);
        printw("%c", ch);
        maze[i][s] = ch;
        if(s==83){
            i+=1;
            s=0;
        }
        s++;
    }
    endwin();

    for(i=0;i<84;i++){
        for(s=0;s<30;s++){
            printf("%c", maze[i][s]);
        }
        printf("\n");
    }

    refresh();

    int y = 1; int x = 1; int prev_y = y; int prev_x = x; int X_direction = 0; int Y_direction = 0; int win = 0;
    
    while(1){
        int ch = getch(); int i;
        switch (ch) {
            case KEY_UP: Y_direction = -1; X_direction = 0; break;  
            case KEY_DOWN: Y_direction = 1; X_direction = 0; break;
            case KEY_LEFT: Y_direction = 0; X_direction = -1; break;
            case KEY_RIGHT: Y_direction = 0; X_direction = 1; break;
        }
        usleep(dificulty);

        x+= X_direction;
        y+= Y_direction;

        move(prev_y,prev_x);
        printw(" ");
        prev_x = x; prev_y = y;
        move(y, x);
        printw("X");
        refresh();

        if((y <= 0) || (x<= 0) || (y >= 30) || (x>= 83)){
            break;
        }        
        /*
        if(maze[x][y] != ' '){
            break;
        }      
        */
    }

    if(win == 0)
    {
        clear();
        si_skoncil();
    }

    fclose(maze1);
}

void init()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr,TRUE);
    curs_set(FALSE);
    nodelay(stdscr, TRUE);
}

void menu(int dificulty)
{
    // prints sth to screen (y,x)
    move(LINES/2, COLS/2);
    printw("PAVOR 2.0");
    move((LINES/2)+1, COLS/2);
    printw("Press Enter to start!");

    refresh();

    int c = 0;
    while(c!='\n'){
        c = getch();
    }
    clear();
    prvy_level(dificulty);
}

void si_skoncil()
{
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_WHITE);
    attron(COLOR_PAIR(1));

    clear();
    char ch;
    FILE *koncis = fopen("si_skoncil60.txt", "r");
    refresh();

    while(ch!=EOF)
    {
        ch = fgetc(koncis);
        printw("%c", ch);
    }

    refresh();
    sleep(3);
    clear();

    move(LINES/2, COLS/2);
    printw("SI SKONCIL!");
    move((LINES/2)+1, (COLS/2));
    printw("Press Enter");
    refresh();

    int c = 0;
    while(c!='\n'){
        c = getch();
    }

    attroff(COLOR_PAIR(1));

    fclose(koncis);
}