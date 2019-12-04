#include <stdio.h>

int main(int argc, char* argv[])
{
    FILE *rwFile = fopen(argv[1], "r");

    if(argc != 2){
        fclose(rwFile);
        rwFile = fopen(argv[1], "w");
        fputc('0', rwFile);
        fclose(rwFile);
        return -1;
    }

    int sum = 0; char ch = 0;  

    while(ch = fgetc(rwFile) != EOF){
        if(ch=='a' || ch=='A'){
            ch = fgetc(rwFile);
            if(ch=='n' || ch=='N'){
                ch = fgetc(rwFile);
                if(ch=='a' || ch=='A'){
                    ch = fgetc(rwFile);
                    if(ch=='n' || ch=='N'){
                        ch = fgetc(rwFile);
                        if(ch=='a' || ch=='A'){
                            ch = fgetc(rwFile);
                            if(ch=='s' || ch=='S'){
                                sum++;
                            }
                        }
                    }
                }
            }
        }
    }

    if(sum == 0){
        fclose(rwFile);
        rwFile = fopen(argv[1], "w");
        fputc('0', rwFile);
        fclose(rwFile);
        return 0;
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
    rwFile = fopen(argv[1], "w");

    for(int i=0;i<size;i++){
        char c = (char)result[i] + 48; 
        fputc(c, rwFile);
    }


    fclose(rwFile);    
    return 0;
}
