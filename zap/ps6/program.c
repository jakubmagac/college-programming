#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

void init();
void menu(int dificulty);
void si_skoncil();
void si_vyhral();
void prvy_level(int dificulty);

int main(int argc, char *argv[])
{
    int dificulty; 
    if( argc == 2 ) {
        switch (argv[1][0]){
            case 'e':
                dificulty = 100000;
                break;

            case 'm':
                dificulty = 50000;
                break;
            
            case 'h':
                dificulty = 25000;
                break;
            
            default:
                printf("Wrong use of argument!");
                break;
            }
        
    }
    else if( argc > 2 ) {
        printf("Too many arguments supplied.\n");
        return 0;
    }
    else {
        printf("One argument expected.\n");
        return 0;
    }

    init();
    menu(dificulty);
    endwin();
    attroff(COLOR_PAIR(1));
    return 0;
}
void prvy_level(int dificulty)
{
    clear();
    char ch;
    FILE *maze1 = fopen("maze1.txt", "r");
    refresh();
    char maze[30][85];
    int i=0; int s = 0;

    for(i=0;i<30;i++){
        for(s=0;s<85;s++){
            ch = fgetc(maze1);
            printw("%c", ch);
            maze[i][s] = ch;
        }
    }
    endwin();
    refresh();

    int y = 8; int x = 18; int prev_y = y; int prev_x = x; int X_direction = 0; int Y_direction = 0; int win = 0;
    
    while(1){
        int ch = getch(); 
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

        if(maze[y][x] == '*' || maze[y][x] == '#'){
            break;
        }   
        if(maze[y][x] == 'O'){
            win = 1;
            break;
        }      
    }

    if(win == 0){
        clear();
        si_skoncil();
    }else{
        clear();
        si_vyhral();
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
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(1));
}

void menu(int dificulty)
{
    // prints sth to screen (y,x)
    move(LINES/2, COLS/2);
    printw("Scary ZAP maze");
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
    fclose(koncis);
}

void si_vyhral()
{
    char ch;
    clear();
    refresh();

    move(LINES/2, COLS/2);
    printw("SI VYHRAL!");
    move((LINES/2)+1, (COLS/2));
    printw("Press Enter");
    refresh();

    int c = 0;
    while(c!='\n'){
        c = getch();
    }
}