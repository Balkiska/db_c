#ifndef TABLE_H
#define TABLE_H

#include <stdbool.h>

// Declaration of table_insert to insert a row into the table
bool table_insert(int id, char* name);

// Declaration of table_select to display all rows in the table
void table_select();

#endif
