#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *rFile;
    FILE *wFile;

    rFile = fopen("file.txt","r"); 
    wFile = fopen("file1.txt","w");

    char ananas[] = {'n','a','n','a','s'};
    int sum = 0; char ch = 0; int same = 1; 

    while(ch != EOF){
        ch = fgetc(rFile);
        if(ch=='a' || ch=='A'){
            for(int i=0;i<5;i++){
                ch = fgetc(rFile);
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

    for(int i=0;i<size;i++){
        char c = (char)result[i] + 48; 
        fputc(c, wFile);
    }


    fclose(wFile);
    fclose(rFile);    
    return 0;
}
