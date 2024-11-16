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

void print_tree(BTreeNode* root);
void free_tree(BTreeNode* root);

#endif 
