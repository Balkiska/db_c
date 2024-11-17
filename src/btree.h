#ifndef BTREE_H
#define BTREE_H

#include "row.h"

// Nodes
typedef struct BTreeNode {
    Row* row;                   
    struct BTreeNode* left;     
    struct BTreeNode* right;    
} BTreeNode;

BTreeNode* search_by_id(BTreeNode* root, int id);
BTreeNode* search_by_name(BTreeNode* root, const char* name);
BTreeNode* search_by_email(BTreeNode* root, const char* email);
BTreeNode* new_node(Row* row);
BTreeNode* insert(BTreeNode* root, Row* row);
Row* new_row(int id, const char* name, const char* email);
void save_tree_to_disk(BTreeNode* root);
BTreeNode* load_tree_from_disk();
BTreeNode* delete_by_id(BTreeNode* root, int id);
void backup_database(BTreeNode* root, const char* filename);
BTreeNode* restore_database(const char* filename);

void free_row(Row* row);
void free_tree(BTreeNode* root);
void print_tree(BTreeNode* root);
void print_tree(BTreeNode* root);
void free_tree(BTreeNode* root);

#endif 
