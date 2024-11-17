#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"

// Nodes structure
BTreeNode* new_node(Row* row) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->row = row;
    node->left = NULL;
    node->right = NULL;
    return node;
}

BTreeNode* insert(BTreeNode* root, Row* row) {
    if (root == NULL) {
        return new_node(row);
    }

    if (row->id < root->row->id) {
        root->left = insert(root->left, row);
    }
    else if (row->id > root->row->id) {
        root->right = insert(root->right, row);
    }

    return root;
}

// Search by ID 
BTreeNode* search_by_id(BTreeNode* root, int id) {
    if (root == NULL || root->row->id == id) {
        return root;
    }

    // Search both subtrees as id could be anywhere
    BTreeNode* left_result = search_by_id(root->left, id);
    if (left_result != NULL) {
        return left_result;
    }

    return search_by_id(root->right, id);
}

// Search by name 
BTreeNode* search_by_name(BTreeNode* root, const char* name) {
    if (root == NULL || strcmp(root->row->name, name) == 0) {
        return root;
    }

    // Search both subtrees as name could be anywhere
    BTreeNode* left_result = search_by_name(root->left, name);
    if (left_result != NULL) {
        return left_result;
    }

    return search_by_name(root->right, name);
}

// Search by email
BTreeNode* search_by_email(BTreeNode* root, const char* email) {
    if (root == NULL || strcmp(root->row->email, email) == 0) {
        return root;
    }

    // Search both subtrees as email could be anywhere
    BTreeNode* left_result = search_by_email(root->left, email);
    if (left_result != NULL) {
        return left_result;
    }

    return search_by_email(root->right, email);
}

//Print
void print_tree(BTreeNode* root) {
    if (root != NULL) {
        print_tree(root->left);
        print_row(root->row);
        print_tree(root->right);
    }
}

// Free nodes
void free_tree(BTreeNode* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free_row(root->row);
        free(root);
    }
}
