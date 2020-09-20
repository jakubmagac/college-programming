CC = gcc
CFLAGS = -std=c11 -Wall -Werror
LDLIBS = -lm
OUTPUT = ps99
all: $(OUTPUT)

$(OUTPUT): track.o playlist.o main.o 
	$(CC) $(CFLAGS) $(LDLIBS) track.o playlist.o main.o -o $(OUTPUT)

main.o: main.c
	$(CC) $(CFLAGS) $(LDLIBS) -c main.c -o main.o

track.o: track.c track.h
	$(CC) $(CFLAGS) $(LDLIBS) -c track.c -o track.o

playlist.o: playlist.c playlist.h
	$(CC) $(CFLAGS) $(LDLIBS) -c playlist.c -o playlist.o

clean:
	rm -rf $(OUTPUT) *.o