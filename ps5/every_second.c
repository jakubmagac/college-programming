#include <stdio.h>

void find_start();

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

    while(ch != EOF){
        if(ch=='S'){
            if((ch=fgetc(rFile))=='T'){
                if((ch=fgetc(rFile))=='A'){
                    if((ch=fgetc(rFile))=='R'){
                        if((ch=fgetc(rFile))=='T'){
                            if((ch=fgetc(rFile))==' '){
                                ch = fgetc(rFile);
                                break;
                            }
                        }
                    }
                }
            }
        }
        ch = fgetc(rFile);
    }

    // uz je na prvom slove
    while(ch != EOF){
        while(ch != ' ' && ch != EOF){
            if(ch == 'S'){
                if((ch=fgetc(rFile))=='T'){
                    if((ch=fgetc(rFile))=='O'){
                        if((ch=fgetc(rFile))=='P'){
                            stop = 1;
                            break;
                        }
                    }
                }
            }else {
                ch = fgetc(rFile);
            }
        }
        if(ch==EOF || stop == 1) break; 
        ch = 0;

        while(ch != ' ' && ch != EOF){
            if((ch=fgetc(rFile))== 'S'){
                if((ch=fgetc(rFile))=='T'){
                    if((ch=fgetc(rFile))=='O'){
                        if((ch=fgetc(rFile))=='P'){
                            stop = 1;
                            break;
                        }
                    }
                }
            }
            if(stop == 1) break;
            if(ch != EOF) fputc(ch, wFile);
        }
        ch = 0;


    }

    fputc('\b', wFile);
    fputc('\0', wFile);
    
    fclose(rFile);
    fclose(wFile);    

    return 0;
}