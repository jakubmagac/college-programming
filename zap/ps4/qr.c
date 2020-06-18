#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>

void encode_char(const char character, bool bits[8]);
char decode_byte(const bool bits[8]);
void encode_string(const char string[], bool bytes[strlen(string)+1][8]);
void decode_bytes(const int rows, bool bytes[rows][8], char string[rows]);
void bytes_to_blocks(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]);
void blocks_to_bytes(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]);

int main()
{
    return 0;
}

void encode_char(const char character, bool bits[8])
{
    int dec = (int)character;
    int power = 128;

    for(int i=0;i<8;i++) {
        if((dec - power) >= 0){
            bits[i] = true;
            dec -= power;
        }
        else bits[i] = false;
        power /= 2;
    }
}

char decode_byte(const bool bits[8])
{
    int dec = 0;
    int power = 128;

    for(int i=0;i<8;i++) {
        if(bits[i] == true){
            dec += power;
            power /=2;
        }
        else power /=2;
    }
    return (char)dec;
}

/*
*   const char string[] - Reťazec, ktorý je potrebné zakódovať na bajty
*   bool bytes[strlen(string)+1][8] - Dvojrozmerné pole, ktoré na každom riadku obsahuje 1 bajt (8 bitov)
*/
void encode_string(const char string[], bool bytes[strlen(string)+1][8])
{
    bool bits[8];
    int length = strlen(string);
    for(int i=0;i<=length;i++) {
        encode_char(string[i], bits);
        for(int s=0;s<8;s++) {
            bytes[i][s] = bits[s];
        }
    }
}

/*
* const int rows - Počet riadkov poľa bytes a počet znakov reťazca string vrátane terminátora
* bool bytes[rows][8] - Dvojrozmerné pole, ktoré na každom riadku obsahuje 1 bajt (8 bitov)
* char string[rows] - Reťazec, ktorý je potrebné vytvoriť dekódovaním údajov poľa bytes
*/
void decode_bytes(const int rows, bool bytes[rows][8], char string[rows])
{
    for(int i=0;i<rows;i++){
        string[i] = decode_byte(bytes[i]);
    }
}

/*
*   const int cols - Počet stĺpcov pre bloky
*   const int offset - Počet skupín riadkov pre bloky (upravuje počet riadkov pre bloky)
*   bool blocks[offset*8][cols] - Dvojrozmerné pole pre bloky s presne definovaným počtom stĺpcov a riadkov
*   const int rows - Počet riadkov (dĺžka reťazca vrátane terminátora)
*   bool bytes[rows][8] - Dvojrozmerné pole s bajtami kódov pre znaky reťazca
*/
void bytes_to_blocks(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8])
{
    int length = 0; int off = 0;
    for(int k=0;k<offset;k++){
        for(int j=0;j<cols;j++){
            for(int i=0;i<8;i++){
                if(length < rows) blocks[i+off][j] = bytes[length][i]; 
                else blocks[i+off][j] = false;
            }
            length++;
        }
        off +=8;
    }
}

/*
*   const int cols - Počet stĺpcov pre bloky
*   const int offset - Počet skupín riadkov pre bloky (upravuje počet riadkov pre bloky)
*   bool blocks[offset*8][cols] - Dvojrozmerné pole pre bloky s presne definovaným počtom stĺpcov a riadkov
*   const int rows - Počet riadkov (dĺžka reťazca vrátane terminátora)
*   bool bytes[rows][8] - Dvojrozmerné pole s bajtami kódov pre znaky reťazca
*/    
void blocks_to_bytes(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8])
{
    int length = 0; int off = 0;
    for(int k=0;k<offset;k++){
        for(int j=0;j<cols;j++){
            for(int i=0;i<8;i++){
                if(length < rows) bytes[length][i] =  blocks[i+off][j]; 
                else{
                    for(int s=0;s<8;s++){
                        bytes[length][s] = 0;
                    }
                    break;
                }
            }
            length++;
        }
        off +=8;
    }
}