#include <stdio.h>

int main(int argc, char* argv[])
{
    FILE *rFile = fopen(argv[1], "r");
    FILE *wFile;
    wFile = fopen("file.txt","w");

    if(argc != 2){
        rFile = fopen(argv[1], "r");
        fclose(rFile);
        return -1;
    }

    char ch; int stop = 0;

    while(1){
        if((ch=fgetc(rFile))=='S'){
            if((ch=fgetc(rFile))=='T'){
                if((ch=fgetc(rFile))=='A'){
                    if((ch=fgetc(rFile))=='R'){
                        if((ch=fgetc(rFile))=='T'){
                            if((ch=fgetc(rFile))==' '){
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
                if((ch=fgetc(rFile))=='T'){
                    if((ch=fgetc(rFile))=='O'){
                        if((ch=fgetc(rFile))=='P'){
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
                if((ch=fgetc(rFile))=='T'){
                    if((ch=fgetc(rFile))=='O'){
                        if((ch=fgetc(rFile))=='P'){
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

    fclose(rFile);    
    rFile = fopen(argv[1], "w");

    char c = fgetc(wFile); 
    while (c != EOF) 
    { 
        fputc(c, rFile); 
        c = fgetc(wFile); 
    } 

    fclose(wFile);
    fclose(rFile);    
    return 0;
}