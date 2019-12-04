#include <stdio.h>

int main(int argc, char* argv[])
{
    FILE *rwFile = fopen(argv[1], "r");

    if(argc != 2){
      return -1;
    }

    char ananas[] = {'n','a','n','a','s'};
    int sum = 0; char ch = 0; int same = 1; 

    while(ch != EOF){
        ch = fgetc(rwFile);
        if(ch=='a' || ch=='A'){
            for(int i=0;i<5;i++){
                ch = fgetc(rwFile);
                if(ch != ananas[i] && ch != ananas[i] - 32){
                    same = 0;
                    break;
                } 
            }
            if(same==1) sum++;
            else same = 1;
        }
    }

    int size = 0; int copy_sum = sum;
    while(copy_sum!=0){
        copy_sum /= 10;
        size++; 
    }

    int result[size]; int divider = 1;
    for(int i=0;i<size-1;i++){
        divider *= 10;
    }
    
    for(int i=0;i<size;i++){
        result[i] = sum / divider;
        sum %= divider;
        divider /= 10;
    }

    fclose(rwFile);    
    FILE *rwFile = fopen(argv[1], "w");

    for(int i=0;i<size;i++){
        char c = (char)result[i] + 48; 
        fputc(c, rwFile);
    }


    fclose(rwFile);    
    return 0;
}
