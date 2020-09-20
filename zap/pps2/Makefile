CFLAGS = -std=c11 -Wall -Werror -lcurses

all: main.o k.o hof.o
	gcc $(CFLAGS) -lm main.o k.o hof.o -o ps2 -lm

k.o: k.c k.h
	gcc $(CFLAGS) -c k.c -o k.o
hof.o: hof.c hof.h
	gcc $(CFLAGS) -c hof.c -o hof.o
main.o: main.c
	gcc $(CFLAGS) -c main.c -o main.o
clean:
	rm *.o
	