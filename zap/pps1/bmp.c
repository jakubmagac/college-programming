#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

bool check_key(const char* key)
{
    if (key == NULL || strlen(key) < 1) return false;
    else {
        for (int i = 0; i < strlen(key); i++){
            if (key[i] < 65 || key[i] > 122) return false;
            else {
                if (key[i] < 97 && key[i] > 90) return false;
            }
        }
    }
    return true;
}

char *reverse(const char *text)
{ 
  if (text == NULL) {
    return NULL;
  }

  int length = strlen(text) - 1;
  char *result = (char *)malloc(length+5);

  for (int i = 0; i <= length; i++){
    result[i] = toupper(text[length - i]);
  }

  result[length+1] = '\0';
  return result;
}

char *vigenere_encrypt(const char *key, const char *text)
{
  if (!check_key(key)) return NULL;
  if (text == NULL || text[0] == '\0') return NULL;

  int text_length = strlen(text);
  int key_length = strlen(key) -1;
  char *result = (char *)malloc(text_length + 5);
  int shift;
  int s = 0;

  for (int i = 0; i < text_length; i++){

    if (isalpha(text[i]) == 0){
      result[i] = text[i];
      continue;
    }

    if (s == key_length + 1) s = 0;
    shift = tolower(key[s]) - 'a';

    if ((tolower(text[i]) + shift) > 'z') result[i] = toupper('a' + (shift - ('z' - text[i]) - 1));
    else result[i] = toupper(text[i]) + shift;
    s++;

  }

  result[text_length] = '\0';

  return result;

}

char *vigenere_decrypt(const char *key, const char *text)
{
  if (!check_key(key)) return NULL;
  //if (!check_text(text)) return NULL;

  if (text == NULL || text[0] == '\0') return NULL;

  int text_length = strlen(text) - 1;
  int key_length = strlen(key) - 1;
  char *result = (char *)malloc(text_length + 5);
  int shift;
  int s = 0;

  for (int i = 0; i <= text_length; i++){
    if ((text[i] < 'A' || (text[i] > 'Z' && text[i] < 'a') || text[i] > 'z')){
      result[i] = text[i];
      continue;
    }

    if (s == key_length + 1) s = 0;
    shift = tolower(key[s]) - 'a';

    if ((tolower(text[i]) - shift) < 'a') result[i] = tolower('z' - (shift + ('a' - text[i]) - 1));
    else result[i] = tolower(text[i]) - shift;
    s++;
  }

  for (int i = 0; i <= text_length; i++){
    if (text[i] == ' '){
      result[0] = toupper(result[0]);
      break;
    } 
  }

  result[text_length+1]='\0';
  return result;
}

int *charToBin(char character)
{
  int divider = 128;  
  int *result = calloc(9, sizeof(int));
  int dec = (int) character;

  for (int i = 0; i < 8; i++){
    result[i] = dec / divider;
    dec %= divider;
    divider /= 2;
  }

  return result;
}

int *intToBin(int character)
{
  int divider = 128;  
  int *result = calloc(9, sizeof(int));
  int dec = character;

  for (int i = 0; i < 8; i++){
    result[i] = dec / divider;
    dec %= divider;
    divider /= 2;
  }

  return result;
}

int binToInt(int *bin)
{
  int sum = 0;
  int divider = 128;

  for(int i=0;i<8;i++){
    if(bin[i] == 1) sum += divider;
    divider /= 2;
  }

  return sum;
}

unsigned char *bit_encrypt(const char *text)
{
  if (text == NULL || text[0] == '\0' ) {
    return NULL;
  }

  int result[8];
  unsigned char *encrypted = (unsigned char *)malloc(strlen(text)+5 );
  char character;
  int *binary;
  int tmp;

  for(int s=0;s<strlen(text);s++){
    character = text[s];
    binary = charToBin(character);  

    //swap bits
    tmp = binary[1];
    binary[1] = binary[0];
    binary[0] = tmp;

    tmp = binary[3];
    binary[3] = binary[2];
    binary[2] = tmp;

    //first half of result
    for(int i=0;i<4;i++){
      result[i] = binary[i];
    }

    // xor funciton
    for(int i=0;i<4;i++){
      if(binary[i] != binary[i+4]) result[i+4] = 1;
      else result[i+4] = 0;
    }

    free(binary);
    encrypted[s] = binToInt(result);
  }

  encrypted[strlen(text)] = '\0';
  return encrypted;
}

int change(int number)
{
  if(number == 0) number = 1;
  else number = 0;
  return number;
}

char* bit_decrypt(const unsigned char* text)
{
  if (text == NULL || text[0] == '\0' ) {
    return NULL;
  }

  int result[8];
  int character;
  int *binary;
  int tmp;

  int size = strlen((char*)text);
  char *decrypted = malloc(size + 2);

  int first_half[4]; 
  int second_half[4];
  int xor[4];

  for(int s=0;s<size+1;s++){
    character = text[s];    
    if(character < 0) character = character * (-1);
    binary = intToBin(character);

    for(int i=0;i<4;i++){
      first_half[i] = binary[i];
      xor[i] = binary[i+4];
    }

    for(int i=0;i<4;i++){
      if(xor[i] == 0) second_half[i] = first_half[i];
      if(xor[i] == 1) second_half[i] = change(first_half[i]);
    }

    tmp = first_half[1];
    first_half[1] = first_half[0];
    first_half[0] = tmp;

    tmp = first_half[3];
    first_half[3] = first_half[2];
    first_half[2] = tmp;

    for(int i = 0;i<4;i++){
      result[i] = first_half[i];
      result[i+4] = second_half[i];
    }

    free(binary);
    decrypted[s] = binToInt(result);
  }

  decrypted[size+1] = '\0';

  return decrypted;
}

unsigned char* bmp_encrypt(const char* key, const char* text)
{
  if (!check_key(key)) return NULL;
  if (text == NULL || text[0] == '\0' ) {
    return NULL;
  }

  char* result = (char*)malloc(sizeof(char) * (1000));
  
  char* reverse_v = reverse(text);
  char* vigenere = vigenere_encrypt(key, reverse_v);
  unsigned char* bit = bit_encrypt(vigenere);

  strcpy((char *)result, (char *)bit);

  free(vigenere);
  free(reverse_v);
  free(bit);
  vigenere = NULL;
  reverse_v = NULL;
  bit = NULL;

  return (unsigned char*)result;
}

char* bmp_decrypt(const char* key, const unsigned char* text)
{
  if (!check_key(key)) return NULL;
  if (text == NULL || text[0] == '\0' ) {
    return NULL;
  }

  char* result = (char*)malloc(sizeof(char) * (1000));

  char* bit = bit_decrypt(text);
  char* vigenere = vigenere_decrypt(key, bit);
  char* reverse_v = reverse(vigenere);

  for(int i=0;i<strlen(reverse_v);i++){
    reverse_v[i] = tolower(reverse_v[i]); 
    if(reverse_v[i] == ' ') reverse_v[0] = toupper(reverse_v[0]);
  }

  strcpy(result, reverse_v);

  free(vigenere);
  free(reverse_v);
  free(bit);
  vigenere = NULL;
  reverse_v = NULL;
  bit = NULL;
  return result;
}
