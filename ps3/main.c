#include "hangman.h"
#include <stdio.h>

int main()
{
    //hangman(get_word());
    printf("%d\n", is_word_guessed("secret", "aeiou"));
    // prints: 0
    printf("%d\n", is_word_guessed("hello", "aeihoul"));

    char result[30];
    get_guessed_word("container", "arpstxgoieyu", result);
    // result = "_o_tai_er"

    printf("%s", result);
    printf("\n");

    char vypis[] = "abcdefghijklmnopqrstuvwxyz";
    get_available_letters("arpstxgoieyu", vypis);
    printf("%s", vypis);
    printf("\n");


    return 0;
}