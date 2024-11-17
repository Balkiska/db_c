# Variables
CC = gcc  # The compiler to use
CFLAGS = -Wall -Wextra -g  # Compiler options
LDFLAGS =  # Linking options

TARGET = db_c  
all: $(TARGET)

# Object files
OBJS = main.o table.o row.o btree.o repl.o

# Linking all object files into the executable (to create the $(TARGET) executable, the $(CC) compiler must link the $(OBJS) object files using the $(CFLAGS) compilation options.)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compiling each source file into object files
main.o: src/main.c table.h row.h btree.h repl.h
	$(CC) $(CFLAGS) -c src/main.c

table.o: src/table.c table.h btree.h row.h
	$(CC) $(CFLAGS) -c src/table.c

row.o: src/row.c row.h
	$(CC) $(CFLAGS) -c src/row.c

btree.o: src/btree.c btree.h row.h
	$(CC) $(CFLAGS) -c src/btree.c

repl.o: src/repl.c repl.h table.h row.h
	$(CC) $(CFLAGS) -c src/repl.c

btree.o: btree.c btree.h row.h
	$(CC) $(CFLAGS) -c src/btree.c
	
# Clean up object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)
or
	rm -f *.o db

# Run the program
run: $(TARGET)
	./$(TARGET)









