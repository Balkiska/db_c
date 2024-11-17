#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"

// Print SEARCH
void print_header() {
    printf("\n");
    printf("+-------------------+-----------------------------+-----------------------------+\n");
    printf("| %-17s | %-27s | %-27s |\n", "ID", "Name", "Email");
    printf("+-------------------+-----------------------------+-----------------------------+\n");
}

// Print a user
void print_user(Row* row) {
    printf("| %-17d | %-27s | %-27s |\n", row->id, row->name, row->email);
}

int main() {
    // some users
    BTreeNode* root = NULL;
    root = insert(root, new_row(571, "moi", "moi@exemple.com"));
    root = insert(root, new_row(294, "moi-même", "moi-même@exemple.com"));
    root = insert(root, new_row(432, "pasmoi", "pasmoi@exemple.com"));

    // Display the users in the tree
    print_header();
    print_tree(root);
    printf("+-------------------+-----------------------------+-----------------------------+\n");

    // Search by ID
    printf("\nSearch by ID (e.g., ID = 571):\n");
    BTreeNode* search_result_id = search_by_id(root, 3);
    if (search_result_id != NULL) {
        print_header();
        print_user(search_result_id->row);
        printf("+-------------------+-----------------------------+-----------------------------+\n");
    } else {
        printf("No user found with this ID !!! try again buddy.\n");
    }

    // Search by Name
    printf("\nSearch by Name (e.g., Name = 'moi'):\n");
    BTreeNode* search_result_name = search_by_name(root, "moi");
    if (search_result_name != NULL) {
        print_header();
        print_user(search_result_name->row);
        printf("+-------------------+-----------------------------+-----------------------------+\n");
    } else {
        printf("No user found with this name!!! try again buddy\n");
    }

    // Search by Email
    printf("\nSearch by Email (e.g., Email = 'moi@exemple.com'):\n");
    BTreeNode* search_result_email = search_by_email(root, "moi@exemple.com");
    if (search_result_email != NULL) {
        print_header();
        print_user(search_result_email->row);
        printf("+-------------------+-----------------------------+-----------------------------+\n");
    } else {
        printf("No user found with this email !!! try again buddy.\n");
    }

    // Save and restore data
    printf("\nSaving and Restoring data...\n");
    save_tree_to_disk(root);
    BTreeNode* loaded_tree = load_tree_from_disk();
    printf("\nTree after restoration:\n");
    print_header();
    print_tree(loaded_tree);
    printf("+-------------------+-----------------------------+-----------------------------+\n");
  
    // Save the tree to disk
    save_tree_to_disk(root);

    // Load tree from disk
    BTreeNode* loaded_tree = load_tree_from_disk();
    print_tree(loaded_tree);

    // Free the memory
    free_tree(root);
    free_tree(loaded_tree);

    return 0;
}




