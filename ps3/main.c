#include "hangman.h"
#include <stdio.h>

int main()
{
    //hangman(get_word());
    printf("%d\n", is_word_guessed("secret", "aeiou"));
    // prints: 0
    printf("%d\n", is_word_guessed("hello", "aeihoul"));
    return 0;
}