#include "hangman.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    char secret[15];
    srand(time(NULL));
    get_word(secret);
    hangman(secret);
    return 0;
}