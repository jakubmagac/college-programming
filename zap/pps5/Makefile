#variables
CC = gcc
CFLAGS = -std=c11 -Wall -Werror
LDLIBS = -lm -g
OUTPUT = ps5

#targets
all: $(OUTPUT)

$(OUTPUT): main.o backpack.o command.o container.o game.o item.o parser.o room.o world.o
	# cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) main.o backpack.o command.o container.o game.o item.o parser.o room.o world.o $(LDLIBS) -o $(OUTPUT)

main.o: main.c
	# cppcheck --enable=performance,unusedFunction --error-exitcode=1 main.c
	$(CC) $(CFLAGS) main.c $(LDLIBS) -c -o main.o

backpack.o: backpack.h backpack.c
	# cppcheck --enable=performance,unusedFunction --error-exitcode=1 backpack.c
	$(CC) $(CFLAGS) backpack.c $(LDLIBS) -c -o backpack.o

command.o: command.h command.c
	# cppcheck --enable=performance,unusedFunction --error-exitcode=1 command.c
	$(CC) $(CFLAGS) command.c $(LDLIBS) -c -o command.o

container.o: container.h container.c
	# cppcheck --enable=performance,unusedFunction --error-exitcode=1 container.c
	$(CC) $(CFLAGS) container.c $(LDLIBS) -c -o container.o

game.o: game.h game.c
	# cppcheck --enable=performance,unusedFunction --error-exitcode=1 game.c
	$(CC) $(CFLAGS) game.c $(LDLIBS) -c -o game.o

item.o: item.h item.c
	# cppcheck --enable=performance,unusedFunction --error-exitcode=1 item.c
	$(CC) $(CFLAGS) item.c $(LDLIBS) -c -o item.o

parser.o: parser.h parser.c
	# cppcheck --enable=performance,unusedFunction --error-exitcode=1 parser.c
	$(CC) $(CFLAGS) parser.c $(LDLIBS) -c -o parser.o

room.o: room.h room.c
	# cppcheck --enable=performance,unusedFunction --error-exitcode=1 room.c
	$(CC) $(CFLAGS) room.c $(LDLIBS) -c -o room.o

world.o: world.h world.c
	# cppcheck --enable=performance,unusedFunction --error-exitcode=1 world.c
	$(CC) $(CFLAGS) world.c $(LDLIBS) -c -o world.o

clean:
	rm -rf $(OUTPUT)
	rm -rf *.o
	clear