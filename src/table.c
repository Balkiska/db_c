#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "table.h"

// Row and table structures 
typedef struct {
    int id;
    char name[666]; 
} Row;

typedef struct {
    Row rows[666]; 
    int row_count;   
} Table;

// Initialize
Table table = {.row_count = 0};

// Insert a rowz into the table
bool table_insert(int id, char* name) {
    if (table.row_count >= 666) {
        printf("Error: Table is full!!!!!\n");
        return false;
    }

    Row row;
    row.id = id;
    strncpy(row.name, name, sizeof(row.name) - 1);
    row.name[sizeof(row.name) - 1] = '\0';  
    table.rows[table.row_count] = row;
    table.row_count++;
    return true;
}

// Display all rowz in the table
void table_select() {
    printf("Displaying all rows:\n");
    for (int i = 0; i < table.row_count; i++) {
        printf("(%d, %s)\n", table.rows[i].id, table.rows[i].name);
    }
}
