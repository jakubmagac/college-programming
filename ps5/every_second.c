#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *rFile = fopen("file.txt", "r");
    FILE *wFile = fopen("file1.txt", "w");
    char ch; int stop = 0;

    while(1){
        if(ch=fgetc(rFile)=='S'){
            if(ch=fgetc(rFile)=='T'){
                if(ch=fgetc(rFile)=='A'){
                    if(ch=fgetc(rFile)=='R'){
                        if(ch=fgetc(rFile)=='T'){
                            if(ch=fgetc(rFile)==' '){
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    while(1){
        do{
            ch=fgetc(rFile);
            if(ch=='S'){
                if(ch=fgetc(rFile)=='T'){
                    if(ch=fgetc(rFile)=='O'){
                        if(ch=fgetc(rFile)=='P'){
                                    stop = 1;
                                    break;
                        }
                    }
                }
            }
        }while(ch != ' ');
        if(stop==1) break;

        do{
            ch=fgetc(rFile);
            if(ch=='S'){
                if(ch=fgetc(rFile)=='T'){
                    if(ch=fgetc(rFile)=='O'){
                        if(ch=fgetc(rFile)=='P'){
                                    stop = 1;
                                    break;
                        }
                    }
                }
            }
            fputc(ch,wFile);
        }while(ch != ' ');
        if(stop==1) break;
    }

    fclose(wFile);
    fclose(rFile);    
    return 0;
}