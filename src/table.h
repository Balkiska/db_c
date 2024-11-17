#ifndef TABLE_H
#define TABLE_H

// Rowz structure
typedef struct {
    int id;
    char* name;
    char* email;
} Row;

// Functions
void backup_database();
BTreeNode* insert(BTreeNode* root, Row* row);
BTreeNode* search_by_id(BTreeNode* root, int id);
BTreeNode* search_by_name(BTreeNode* root, const char* name);

#endif
