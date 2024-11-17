#ifndef TABLE_H
#define TABLE_H
#include "btree.h"
#include "row.h"
#include <stdbool.h>

// Table structure
typedef struct {
    Row* rows;
    int num_rows;
    int max_rows;
    BTreeNode* index; 
} Table;

// Functions
Table* new_table(void);
void free_table(Table* table);
bool insert_row(Table* table, int id, const char* name, const char* email);
void select_all_rows(Table* table);
void select_row_by_id(Table* table, int id);
void select_row_by_name(Table* table, const char* name);
void select_row_by_email(Table* table, const char* email);

#endif
