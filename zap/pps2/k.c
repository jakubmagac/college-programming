#include <stdlib.h>
#include<stdio.h>
#include <stdbool.h> 
#include <math.h>
#include "k.h"

void add_random_tile(struct game *game)
{
    int row, col;
    do{
        row = rand() % SIZE;
        col = rand() % SIZE;
    }while(game->board[row][col] != ' ');

    if(rand() % 2 == 0){
        game->board[row][col] = 'A';
    }else{
        game->board[row][col] = 'B';
    }
}

bool is_game_won(const struct game game)
{
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(game.board[i][j] == 'K') return true;
        }
    }

    return false;
}

bool is_move_possible(const struct game game)
{
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(game.board[i][j] == ' ') return true;
        }
    }

    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if((game.board[i][j] == game.board[i][j-1] && j!=0)     ||
               (game.board[i][j] == game.board[i][j+1] && j+1!=SIZE)||
               (game.board[i][j] == game.board[i-1][j] && i!=0)     ||
               (game.board[i][j] == game.board[i+1][j] && i+1!=SIZE)) return true;
        }
    }

    return false;
}

bool update(struct game *game, int dy, int dx)
{
    if((dy == 1 && dx ==  1) || (dy ==  0 && dx == 0) || (dy == -1 && dx == -1) ) return false;
    if((dy == 1 && dx == -1) || (dy == -1 && dx == 1) ) return false;
    if(dy != 1 && dy != 0 && dy != -1) return false;
    if(dx != 1 && dx != 0 && dx != -1) return false;

    char array[SIZE];
    char arrayM[SIZE];
    char arrayCheck[SIZE][SIZE];
    int counter = 0;
    int s;
    int score = 0;

    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            arrayCheck[i][j] = game->board[i][j];
        }
    }

    if(dx == 1){
        for(int i=0;i<SIZE;i++){
        
            //inicialize arrays
            for(int j=0;j<SIZE;j++){
                array[j] = ' ';
                arrayM[j] = ' ';
            };

            // FIND
            counter = 0;
            for(int j=0;j<SIZE;j++){
                if(game->board[i][j] != ' '){
                    array[counter] = game->board[i][j];
                    counter++;
                }
            }

            // MERGE
            while(counter != 0){
                if(array[counter] == array[counter-1]){
                    score += (int)pow(2, ( (int)array[counter] - 64 )) * 2;
                    array[counter-1]++;
                    array[counter] = ' ';
                    
                    // may solve or cause problems
                    if(counter-1 == 0){
                        counter--;
                        break; 
                    } 

                    if(array[counter-1]==array[counter-2]) counter--;
                }
                counter--;
            }

            int k=0;
            for(int j=0;j<SIZE;j++){
                if(array[j] != 32){
                    arrayM[k] = array[j];
                    k++;
                }
            }

            //PLACE
            counter = 0;
            for(int j=0;j<SIZE;j++){
                if(arrayM[j] == ' ') break;
                counter++;
            }
            
            s=0;
            for(int j=0;j<SIZE;j++){
                if(j < SIZE-counter) game->board[i][j] = ' ';
                else{
                    game->board[i][j] = arrayM[s];
                    s++;
                } 
            }
        }
    }

    if(dx == -1){
        for(int i=0;i<SIZE;i++){
            //inicialize arrays
            for(int j=0;j<SIZE;j++){
                array[j] = ' ';
                arrayM[j] = ' ';
            };

            // FIND
            counter = 0;
            for(int j=0;j<SIZE;j++){
                if(game->board[i][j] != ' '){
                    array[counter] = game->board[i][j];
                    counter++;
                }
            }

            // MERGE
            counter = 0;
            while(counter+1 < SIZE){
                if(array[counter] == array[counter+1]){
                    score += (int)pow(2, ( (int)array[counter] - 64 )) * 2;
                    if(array[counter]!=' ') array[counter]++;
                    array[counter+1] = ' ';

                    // may solve or cause problems
                    if(counter+2 == SIZE){
                        counter++;
                        break; 
                    } 

                    if(array[counter+1]==array[counter+2]) counter++;
                }
                counter++;
            }

            counter = 0;
            for(int j=0;j<SIZE;j++){
                if(array[j] != 32){
                    arrayM[counter] = array[j];
                    counter++;
                }
            }

            //PLACE
            for(int j=0;j<SIZE;j++){
                if(arrayM[j] == ' ') game->board[i][j] = ' ';
                else game->board[i][j] = arrayM[j];
            }

        }
    }

    if(dy == 1){
        for(int i=0;i<SIZE;i++){
        
            //inicialize arrays
            for(int j=0;j<SIZE;j++){
                array[j] = ' ';
                arrayM[j] = ' ';
            };

            // FIND
            counter = 0;
            for(int j=0;j<SIZE;j++){
                if(game->board[j][i] != ' '){
                    array[counter] = game->board[j][i];
                    counter++;
                }
            }

            // MERGE
            while(counter != 0){
                if(array[counter] == array[counter-1]){
                    score += (int)pow(2, ( (int)array[counter] - 64 )) * 2;
                    array[counter-1]++;
                    array[counter] = ' ';

                    // may solve or cause problems
                    if(counter-1 == 0){
                        counter--;
                        break; 
                    } 

                    if(array[counter-1]==array[counter-2]) counter--;
                }
                counter--;
            }

            int k=0;
            for(int j=0;j<SIZE;j++){
                if(array[j] != 32){
                    arrayM[k] = array[j];
                    k++;
                }
            }

            //PLACE
            counter = 0;
            for(int j=0;j<SIZE;j++){
                if(arrayM[j] == ' ') break;
                counter++;
            }
            
            s=0;
            for(int j=0;j<SIZE;j++){
                if(j < SIZE-counter) game->board[j][i] = ' ';
                else{
                    game->board[j][i] = arrayM[s];
                    s++;
                } 
            }
        }
    }

    if(dy == -1){
        for(int i=0;i<SIZE;i++){
        
            //inicialize arrays
            for(int j=0;j<SIZE;j++){
                array[j] = ' ';
                arrayM[j] = ' ';
            };

            // FIND
            counter = 0;
            for(int j=0;j<SIZE;j++){
                if(game->board[j][i] != ' '){
                    array[counter] = game->board[j][i];
                    counter++;
                }
            }

            // MERGE
            counter = 0;
            while(counter+1 < SIZE){
                if(array[counter] == array[counter+1]){
                    score += (int)pow(2, ( (int)array[counter] - 64 )) * 2;
                    if(array[counter]!=' ') array[counter]++;
                    array[counter+1] = ' ';

                    // may solve or cause problems
                    if(counter+2 == SIZE){
                        counter++;
                        break; 
                    } 

                    if(array[counter+1]==array[counter+2]) counter++;
                }
                counter++;
            }

            counter = 0;
            for(int j=0;j<SIZE;j++){
                if(array[j] != 32){
                    arrayM[counter] = array[j];
                    counter++;
                }
            }

            //PLACE
            for(int j=0;j<SIZE;j++){
                if(arrayM[j] == ' ') game->board[j][i] = ' ';
                else game->board[j][i] = arrayM[j];
            }
        }
    }

    game->score += score;

    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(game->board[i][j] != arrayCheck[i][j]) return true;
        }
    }

    return false;
}