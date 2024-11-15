#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

// Create a new andd empty table
Table* new_table() {
    Table* table = (Table*)malloc(sizeof(Table));
    table->rows = NULL;
    table->num_rows = 0;
    table->max_rows = 0;
    return table;
}

// Row gestions of the table
void add_row(Table* table, int id, const char* name, const char* email) {
    if (table->num_rows == table->max_rows) {
        table->max_rows = (table->max_rows == 0) ? 1 : table->max_rows * 2;
        table->rows = (Row*)realloc(table->rows, sizeof(Row) * table->max_rows);
    }
    table->rows[table->num_rows].id = id;
    table->rows[table->num_rows].name = strdup(name);
    table->rows[table->num_rows].email = strdup(email);
    table->num_rows++;
}

// Print
void print_table(Table* table) {

    printf("ID | Name | Email\n");
    printf("---+------+-------\n");

    for (int i = 0; i < table->num_rows; i++) {
        printf("%d | %s | %s\n", table->rows[i].id, table->rows[i].name, table->rows[i].email);
    }
