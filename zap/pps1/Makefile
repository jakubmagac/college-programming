CFLAGS = -std=c11 -Wall -Werror

all: main.c bmp.o playfair.o
	gcc $(CFLAGS) -lm main.c bmp.o playfair.o -o ps1 -lm

bmp.o: bmp.c bmp.h
	gcc $(CFLAGS) -c bmp.c -o bmp.o
playfair.o: playfair.c playfair.h
	gcc $(CFLAGS) -c playfair.c -o playfair.o
main.o: main.c
	gcc $(CFLAGS) -c main.c -o main.o
clean:
	rm *.o
	
