#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"
#include <unistd.h>
#include <fcntl.h>

// Row structure
typedef struct {
    int id;
    char* name;
    char* email; 
} Row;

// Structure for a node
typedef struct BTreeNode {
    Row* row; 
    struct BTreeNode* left; 
    struct BTreeNode* right; 
} BTreeNode;

// Node management
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

    if (id < root->row->id) {
        return search_by_id(root->left, id);  
    } else {
        return search_by_id(root->right, id); 
    }
}

// Search by name 
BTreeNode* search_by_name(BTreeNode* root, const char* name) {
    if (root == NULL) {
        return NULL;  
    }

    if (strcmp(root->row->name, name) == 0) {
        return root;  
    }

    BTreeNode* left_search = search_by_name(root->left, name);
    if (left_search != NULL) {
        return left_search;
    }
    return search_by_name(root->right, name); 
}

// Search by email
BTreeNode* search_by_email(BTreeNode* root, const char* email) {
    if (root == NULL) {
        return NULL; 
    }

    if (strcmp(root->row->email, email) == 0) {
        return root;  
    }

    BTreeNode* left_search = search_by_email(root->left, email);
    if (left_search != NULL) {
        return left_search;
    }
    return search_by_email(root->right, email);  

void print_tree(BTreeNode* root) {
    if (root != NULL) {
        print_tree(root->left);
        print_row(root->row);
        print_tree(root->right);
    }
}

// Function do delete node by id
BTreeNode* delete_by_id(BTreeNode* root, int id) {
    if (root == NULL) {
        return NULL;
    }

    if (id < root->row->id) {
        root->left = delete_by_id(root->left, id);  
    } else if (id > root->row->id) {
        root->right = delete_by_id(root->right, id); 
    } else {
        if (root->left == NULL) {
            BTreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            BTreeNode* temp = root->left;
            free(root);
            return temp;
        }

        BTreeNode* min_larger_node = root->right;
        while (min_larger_node && min_larger_node->left != NULL) {
            min_larger_node = min_larger_node->left;
        }

        root->row = min_larger_node->row;
        root->right = delete_by_id(root->right, min_larger_node->row->id); 
    }
    return root;
}

// Show the tree 
void print_in_order(BTreeNode* root) {
    if (root != NULL) {
        print_in_order(root->left);
        printf("ID: %d, Name: %s, Email: %s\n", root->row->id, root->row->name, root->row->email);
        print_in_order(root->right);
    }
}
void backup_database(BTreeNode* root, const char* filename) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("Error opening file for backup !!!!!!!");
        return;
    }
    backup_recursive(root, fd);
    close(fd);
}

// Recursive saving of the tree
void backup_recursive(BTreeNode* root, int fd) {
    if (root == NULL) {
        return;
    }

    write(fd, &root->row->id, sizeof(int));  
    write(fd, root->row->name, strlen(root->row->name) + 1); 
    write(fd, root->row->email, strlen(root->row->email) + 1); 
    backup_recursive(root->left, fd);  
    backup_recursive(root->right, fd);  
}

// Function to restore data from a file
BTreeNode* restore_database(const char* filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for restoration");
        return NULL;
    }

    BTreeNode* root = NULL;
    restore_recursive(&root, fd);
    close(fd);
    return root;
}

// Recursive restoration of the tree
void restore_recursive(BTreeNode** root, int fd) {
    int id;
    char name[666];
    char email[666];

    while (read(fd, &id, sizeof(int)) > 0) {
        read(fd, name, sizeof(name));
        read(fd, email, sizeof(email));

        Row* row = (Row*)malloc(sizeof(Row));
        row->id = id;
        row->name = strdup(name);
        row->email = strdup(email);

        *root = insert(*root, row)
    }
}

//Free rowz
void free_row(Row* row) {
    if (row != NULL) {
        free(row->name);   
        free(row->email); 
        free(row);       
    }
}

//Free tree
void free_tree(BTreeNode* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free_row(root->row);
        free(root);
    }
}
