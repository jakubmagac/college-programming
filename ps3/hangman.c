#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "hangman.h"
#include <string.h>


/*int get_word(char secret[]){
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
}*/

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
    {
        guessed_word[i] = '_';
    }

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
}

void get_available_letters(const char letters_guessed[], char available_letters[]) 
{
    int size_guessed = strlen(letters_guessed);
    int size_available = strlen(available_letters);

    for(int i=0;i<size_guessed;i++)
    {
        for(int s=0;s<size_available;s++)
        {
            if(letters_guessed[i] == available_letters[s])
            {
                available_letters[s] = '*';
            }
        }
    }
    for(int s=0;s<size_available;s++)
    {
        if(available_letters[s]=='*')
        {
            for(int i=s;i<size_available;i++){
                available_letters[i] = available_letters[i+1];
            }
            if(available_letters[i+1] == '*') i--;


        }
    }
}