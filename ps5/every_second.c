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
                            break;
                        }
                    }
                }
            }else {
                ch = fgetc(rFile);
            }
        }
        if(ch==EOF) break;
        ch = 0;

        while(ch != ' ' && ch != EOF){
            if((ch=fgetc(rFile))== 'S'){
                if((ch=fgetc(rFile))=='T'){
                    if((ch=fgetc(rFile))=='O'){
                        if((ch=fgetc(rFile))=='P'){
                            break;
                        }
                    }
                }
            }
            if(ch != EOF) fputc(ch, wFile);
        }


    }
    
    fclose(rFile);
    fclose(wFile);    

    return 0;
}