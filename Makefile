# Variables
CC = gcc  # The compiler to use
CFLAGS = -Wall -Wextra -g  # Compiler options
LDFLAGS =  # Linking options

# Rules
all: db_c  # Default rule to create the executable

db_c: main.o db.o  # The executable depends on object files
	$(CC) $(LDFLAGS) -o db_c main.o db.o  # Command to create the executable

main.o: main.c  # Compile main.c into main.o
	$(CC) $(CFLAGS) -c main.c

db.o: db.c db.h  # Compile db.c into db.o
	$(CC) $(CFLAGS) -c db.c

clean:  # Rule to remove object files and the executable
	rm -f *.o db_c
