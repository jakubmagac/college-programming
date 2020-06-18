#include <stdio.h>

void find_start();

int main(int argc, char* argv[])
{
    FILE *rFile = fopen(argv[1], "r");
    FILE *wFile = fopen(argv[2], "w");
    int stop = 0; int stop_char[3] = {0,0,0};

    char ch = fgetc(rFile);
    if(ch == EOF){
        fclose(rFile);
        fclose(wFile);
        return 0;
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
            for (int i = 0; i < 3 ; i++)
                stop_char[i] = 0; 
            if((ch=fgetc(rFile))== 'S'){
                stop_char[0] = 1;
                if((ch=fgetc(rFile))=='T'){
                    stop_char[1] = 1;
                    if((ch=fgetc(rFile))=='O'){
                        stop_char[2] = 1;
                        if((ch=fgetc(rFile))=='P'){
                            stop = 1;
                            break;
                        }
                    }
                }
            }
            if(stop == 1) break;
            if(ch != EOF){
                if(stop_char[0]==1) fputc('S', wFile);
                if(stop_char[1]==1) fputc('T', wFile);
                if(stop_char[2]==1) fputc('O', wFile);
                fputc(ch, wFile);
            } 
        }
        ch = 0;


    }
    
    fclose(rFile);
    fclose(wFile);    

    wFile = fopen(argv[2], "r");
    FILE *helper = fopen("helper.txt", "w");

    ch = 0; int size = 0;
    while(ch!=EOF){
        ch = fgetc(wFile);
        size++;
    }
    size--;

    fclose(wFile);    
    wFile = fopen(argv[2], "r");
    for(int i=0;i<size;i++){
        ch = fgetc(wFile);
        fputc(ch, helper);
    }

    fclose(wFile);    
    fclose(helper);

    wFile = fopen(argv[2], "w");
    helper = fopen("helper.txt", "r");

    for(int i=0;i<size-1;i++){
        ch = fgetc(helper);
        fputc(ch, wFile);
    }

    fclose(helper);
    fclose(wFile);
    return 0;
}