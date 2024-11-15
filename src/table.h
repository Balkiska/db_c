#ifndef TABLE_H
#define TABLE_H

typedef struct {
    int id;
    char* name;
    char* email;
} Row;

typedef struct {
    Row* rows;
    int num_rows;
    int max_rows;
} Table;

Table* new_table();
void insert_row(Table* table, Row* row);
void select_rows(Table* table);

#endif
