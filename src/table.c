#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "table.h"

// Row struct to hold information for each row in the table
typedef struct {
    int id;
    char name[666]; 
} Row;

// A basic table structure to hold multiple rows
typedef struct {
    Row rows[1000];  // Fixed-size array of rows
    int row_count;   // Counter for the number of rows in the table
} Table;

// Initialize a new table
Table table = {.row_count = 0};

// Function to insert a row into the table
bool table_insert(int id, char* name) {
    // Check if the table has space for a new row
    if (table.row_count >= 1000) {
        printf("Error: Table full.\n");
        return false;
    }

    // Create a new row and fill in the details
    Row row;
    row.id = id;
    strncpy(row.name, name, sizeof(row.name) - 1);
    row.name[sizeof(row.name) - 1] = '\0';  // Ensure null-terminated string

    // Insert the row into the table and increment the row count
    table.rows[table.row_count] = row;
    table.row_count++;

    return true;
}

// Function to display all rows in the table
void table_select() {
    printf("Displaying all rows:\n");
    for (int i = 0; i < table.row_count; i++) {
        printf("(%d, %s)\n", table.rows[i].id, table.rows[i].name);
    }
}
