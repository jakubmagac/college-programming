#include <stdio.h>
#include "hof.h"
#include "k.h"
#include "ui.h"

int main()
{
    struct game game = {
      .score=8247,
      .board = {
        {' ', 'C', ' ', 'H'},
        {' ', 'D', 'F', ' '},
        {' ', ' ', 'F', 'F'},
        {' ', ' ', 'J', ' '}
    }};

    printf("%d", is_move_possible(game));

    printf("%d\n", update(&game, 1, 0));
    printf("%d \n", game.score);

    add_random_tile(&game);
    printf("%d\n", is_game_won(game));

    struct player list[10];
    printf("%d", load(list));

    //add 
struct player player = {.name="Bill", .score=1393};
int size=10;
struct player hof[10] = {
    {.score= 1869, .name="Bill"},
    {.score= 1393, .name="Manager"},
    {.score= 1274, .name="Manager"},
    {.score= 1128, .name="John"},
    {.score=  989, .name="Jack"},
    {.score=  648, .name="Samuel"},
    {.score=  261, .name="Samuel"},
    {.score=  241, .name="Jack"},
    {.score=  190, .name="Manager"},
    {.score=   70, .name="John"}
};
    printf("\nADD: %d\n",add_player(hof, &size, player));
    printf("%d \n", save(hof, size));

    render(game);
    return 0;
};
