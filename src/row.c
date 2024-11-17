#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "row.h"

// Create a new row with the given data
Row* new_row(int id, const char* name, const char* email) {
  
    Row* row = (Row*)malloc(sizeof(Row));
    row->id = id;
    row->name = strdup(name);  
    row->email = strdup(email);  
    return row;
}

// Free the memory used by a row
void free_row(Row* row) {
    if (row != NULL) {
        free(row->name);
        free(row->email);
        free(row);
    }
}

// Print
void print_row(Row* row) {
    if (row != NULL) {
        printf("ID: %d | Name: %s | Email: %s\n", 
               row->id, row->name, row->email);
    }
}
