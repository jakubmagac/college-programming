#include <stdio.h>

int main(int argc, char* argv[])
{
    FILE *rFile = fopen(argv[1], "r");
    FILE *wFile = fopen("file1.txt","w");
    int stop = 0; 

    char ch = fgetc(rFile);
    if(ch == EOF){
        fclose(rFile);
        rFile = fopen(argv[1], "w");
        fclose(rFile);
        return -1;
    }

    // Zvysok
    while(1){
        if(ch=='S'){
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
        ch = fgetc(rFile);
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
    fclose(wFile);    

    rFile = fopen(argv[1], "w");
    wFile = fopen("file1.txt","r");

    ch = fgetc(wFile); 
    while (ch != EOF) 
    { 
        fputc(ch, rFile); 
        ch = fgetc(wFile); 
    } 
    return 0;
}