CC = gcc
CFLAGS = -std=c11 -Wall -Werror
LDLIBS = -lm
OUTPUT = ps4
all: $(OUTPUT)

$(OUTPUT): bmp.o transformations.o main.o 
	$(CC) $(CFLAGS) $(LDLIBS) bmp.o transformations.o main.o -o $(OUTPUT)

main.o: main.c
	$(CC) $(CFLAGS) $(LDLIBS) -c main.c -o main.o

bmp.o: bmp.c bmp.h
	$(CC) $(CFLAGS) $(LDLIBS) -c bmp.c -o bmp.o

transformations.o: transformations.c transformations.h
	$(CC) $(CFLAGS) $(LDLIBS) -c transformations.c -o transformations.o

clean:
	rm -rf $(OUTPUT) *.o