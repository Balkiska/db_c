#ifndef ROW_H
#define ROW_H

// Structure for a single row in the table
typedef struct {
    int id;
    char* name;
    char* email;
} Row;

// Prototypes
Row* new_row(int id, const char* name, const char* email);
void free_row(Row* row);
void print_row(Row* row);

#endif 
