# Variables
CC = gcc # The compiler to use
CFLAGS = -Wall -g # Compiler options
LDFLAGS = # Linking options (for the linking phase, but we'll see about that later)

all: db_c # Default target, produces the db_c executable

# Target to create the executable
db_c: main.o db.o # db_c depends on main.o and db.o
	$(CC) $(LDFLAGS) -o db_c main.o db.o # Command to create the executable

# Target for compiling main.o from main.c
main.o: main.c # main.o depends on main.c
	$(CC) $(CFLAGS) -c main.c # Compile main.c into main.o

# Target for compiling db.o from db.c
db.o: db.c db.h # db.o depends on db.c and db.h
	$(CC) $(CFLAGS) -c db.c # Compile db.c into db.o


clean: # Used to delete compiled files
	rm -f *.o db_c
