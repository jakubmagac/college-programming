#include <stdio.h>

int main(int argc, char* argv[])
{
    FILE *rFile = fopen(argv[1], "r");
    FILE *wFile = fopen(argv[2], "w");
    int stop = 0; 

    char ch = fgetc(rFile);
    if(ch == EOF){
        fclose(rFile);
        fclose(wFile);
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

    return 0;
}