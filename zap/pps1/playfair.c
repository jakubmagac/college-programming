#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "playfair.h"


bool check_repetition(char arr[5][5], char c)
{
  for(int i=0;i<5;i++){
    for(int j=0;j<5;j++){
      if(arr[i][j] == toupper(c)) return true;
    }
  }
  return false;
}

char* playfair_encrypt(const char* key, const char* text)
{
  char table[5][5] = {0}; int j=0, k=0;

  // check if text consist only from text and spaces
  for(int i=0;i<strlen(text);i++){
    if(!isalpha(text[i]) && text[i] != ' ') return NULL; 
  }

  int size_key = strlen(key);
  char changed_key[size_key];

  // key without W
  for(int i=0;i<size_key;i++){
    if(toupper(key[i]) == 'W') changed_key[i] = 'V';
    else changed_key[i] = key[i];
  }

  
  for(int i=0; i<size_key; i++){
    if(changed_key[i] == ' ') continue;
    if(!check_repetition(table, changed_key[i])){
      table[j][k] = toupper(changed_key[i]);
      k++;
      if(k==5){
        j++; k=0;
      }
    }
  }


  for(int i=0;i<25;i++){
    if(!check_repetition(table, ALPHA[i])){
      table[j][k] = ALPHA[i];
      k++;
      if(k==5){
        j++; k=0;
      }
    }
  }

  int size_text = strlen(text);

  // uprava pred sifrou
  int rept=0;
  for(int i=0;i<size_text;i++){
    if(text[i] == text[i+1] && toupper(text[i]) != 'X') rept++;
  }
  if((size_text + rept) % 2 != 0) rept++;

  int size_to_cryp = size_text + rept;
  char text_to_enc[size_to_cryp];
  int s=0; int space = 0;

  char text_without_W[size_text];
  for(int i=0;i<size_text;i++){
    if(text[i] == ' ') space++;
    if(text[i] == 'W') text_without_W[i] = 'V';
    else text_without_W[i] = toupper(text[i]);
  }

  char almost_ready[size_text-space];
  for(int i=0;i<size_text;i++){
    if(text_without_W[i] == ' ') continue;
    almost_ready[i] = toupper(text_without_W[i]);
  }



  for(int i=0;i<size_text-space;i++){
    if((almost_ready[i] != almost_ready[i+1]) || ((almost_ready[i]==almost_ready[i+1]) && (almost_ready[i] == 'X'))){
      text_to_enc[s] = almost_ready[i]; s++; i++;
      text_to_enc[s] = almost_ready[i]; s++;
    }else{
      text_to_enc[s] = almost_ready[i]; s++; i++;
      text_to_enc[s] = 'X'; s++;
      text_to_enc[s] = almost_ready[i]; s++; 
    }
  }

  if(s % 2 != 0){
    text_to_enc[s] = 'X'; 
    s++;
  } 
  text_to_enc[s] = '\0';

  char* enc = (char*) calloc((s+(s/2)+1), sizeof(char));
  int first_col;
  int first_row;
  int second_col;
  int second_row;

  for(int j=0;j<5;j++){
      for(int k=0;k<5;k++){
        printf("%c ", table[j][k]);
      }
      printf("\n");
    }

  s = 0;
  for(int i=0;i<size_text+rept-1;i+=2){
    for(int j=0;j<5;j++){
      for(int k=0;k<5;k++){
        if(text_to_enc[i] == table[j][k]){
          first_col = k;
          first_row = j;
        }
        if(text_to_enc[i+1] == table[j][k]){
          second_col = k;
          second_row = j;
        }
      }
    }

    printf("char: %c char+1: %c FR: %d SR: %d FC: %d SC: %d\n", text_to_enc[i], text_to_enc[i+1], first_row, second_row, first_col, second_col);

    // riadok
    if(first_row == second_row){
      if(first_row == 4)  enc[s] = table[first_row][0];
      if(first_row < 4)   enc[s] = table[first_row][first_col+1];
      if(second_row == 4) enc[s+1] = table[second_row][0];
      if(second_row < 4)   enc[s+1] = table[second_row][second_col+1];
      enc[s+2] = ' '; s+=3;
      continue;
    }

    // stlpec
    if(first_col == second_col){
      if(first_col == 4)  enc[s] = table[0][first_col];
      if(first_col < 4)   enc[s] = table[first_row+1][first_col];
      if(second_col == 4) enc[s+1] = table[0][second_col];
      if(first_col < 4)   enc[s+1] = table[second_row+1][second_col];
      enc[s+2] = ' '; s+=3;
      continue;

    }

    if((first_row != second_row) && (first_col != second_col)){
      enc[s]   = table[first_row][second_col];
      enc[s+1] = table[second_row][first_col];
      enc[s+2] = ' '; s+=3;
      continue;

    }


  }
  enc[s-1] = '\0';

  return enc;
}

char* playfair_decrypt(const char* key, const char* text)
{
  return NULL;
}