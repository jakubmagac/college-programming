#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "hangman.h"
#include <string.h>
#include <ctype.h>

int get_word(char secret[]){
    // check if file exists first and is readable
    FILE *fp = fopen(WORDLIST_FILENAME, "rb");
    if( fp == NULL ){
        fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
        return 1;
    }

    // get the filesize first
    struct stat st;
    stat(WORDLIST_FILENAME, &st);
    long int size = st.st_size;

    do{
        // generate random number between 0 and filesize
        long int random = (rand() % size) + 1;
        // seek to the random position of file
        fseek(fp, random, SEEK_SET);
        // get next word in row ;)
        int result = fscanf(fp, "%*s %20s", secret);
        if( result != EOF )
            break;
    }while(1);

    fclose(fp);

    return 0;
}

// just comment so I can have 10 contrib/ day

int is_word_guessed(const char secret[], const char letters_guessed[])
{
    int size_secret = strlen(secret);
    int size_guessed = strlen(letters_guessed);

    char copy_secret[size_secret];
    for(int i = 0; i < size_secret; i++) {
        copy_secret[i] = secret[i];
    }
    
    char copy_guessed[size_guessed];
    for(int i = 0; i < size_guessed; i++) {
        copy_guessed[i] = letters_guessed[i];
    }

    for(int i=0;i<size_secret;i++)
    {
        for(int s=0;s<size_guessed;s++)
        {
            if(copy_secret[i] == copy_guessed[s])
            {
                copy_secret[i] = '*';
            }
        }
    }

    for(int i=0;i<size_secret;i++)
    {
        if(copy_secret[i] != '*') return 0;
    }
    return 1;
}

void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[])
{
    int size_secret = strlen(secret);
    int size_guessed = strlen(letters_guessed);

    for(int i=0;i<size_secret;i++)
        guessed_word[i] = '_';

    for(int s=0;s<size_guessed;s++)
    {
        for(int i=0;i<size_secret;i++)
        {
            if(secret[i] == letters_guessed[s])
            {
                guessed_word[i] = secret[i];
            }
        }
    }

    guessed_word[size_secret] = '\0';
    for(int i=0;i<size_secret;i++)
        printf("%c ", guessed_word[i]);

}

void get_available_letters(const char letters_guessed[], char available_letters[]) 
{
    char c = 'a';
    for(int i = 0; i < 26; i++){
        available_letters[i] = c;
        c++;
    }
    available_letters[26] = '\0';

    int size_guessed = strlen(letters_guessed);
    int size_available = strlen(available_letters);
    
    for(int i=0;i<size_guessed;i++)
        for(int s=0;s<size_available;s++)
            if(letters_guessed[i] == available_letters[s])
                available_letters[s] = '*';

    if(size_guessed > 0){
        for(int s=0;s<size_available;s++)
            if(available_letters[s]=='*')
            {
                for(int i=s; i<size_available-1; i++)
                    available_letters[i] = available_letters[i + 1];
                if(available_letters[s]=='*') s--;
                available_letters[size_available-1] = '\0';
                size_available--;
            }
    }
}

void hangman(const char secret[])
{
    printf("Welcome to the game, Hangman!\n");
    printf("I am thinking of a word that is %lu letters long.", strlen(secret));

    int numbers_of_chances = 8;
    char letters_guessed[26] = {'\n'};
    char available_letters[26];
    char guessed_word[8]; 
    char guess[10]; 
    char c;
    int j = 0;

    while(numbers_of_chances > 0)
    {
    
        printf("\n-------------\n");

        get_available_letters(letters_guessed, available_letters);
        printf("You have %d guesses left. \nAvailable letters: %s\n", numbers_of_chances, available_letters);
        
        // char prepocitany
        printf("Please guess a letter: ");

        scanf("%9s", guess);
        while (getchar() != '\n') 
            ;   
        
        // rovnako dlhe slovo
        if(strlen(guess) == strlen(secret)){
            for(int i=0;i<strlen(guess);i++)
                letters_guessed[i] = tolower(guess[i]);
            break;    
        }

        c = tolower(guess[0]);

        if(!(c>='a' && c<='z')){
            printf("Oops! %c is not a valid letter: ", c);
            get_guessed_word(secret, letters_guessed, guessed_word);
            continue;
        }
        if(strchr(letters_guessed,c)){
            printf("Oops! You've already guessed that letter: ");
            get_guessed_word(secret, letters_guessed, guessed_word);
            continue;
        }
        
        if(strchr(secret,c)) printf("\nGood guess: ");
        if(!strchr(secret,c)){
           printf("Oops! That letter is not in my word: ");
           numbers_of_chances--;
        }

        letters_guessed[j] = c;
        j++;
        if(is_word_guessed(secret, letters_guessed)) break;
        get_guessed_word(secret, letters_guessed, guessed_word);
   
   
    }
    printf("\n-------------\n");
    if(!is_word_guessed(secret,letters_guessed)) printf("Sorry, you ran out of guesses. The word was %s.\n", secret);
    if(is_word_guessed(secret,letters_guessed)) printf("Congratulations, you won!\n");
}
