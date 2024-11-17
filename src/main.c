#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

void print_separator() {
    printf("+--------------------------------+--------------------------------+--------------------------------+ \n");
}

void print_header() {
    print_separator();
    printf("| %-30s | %-30s | %-30s |\n", "ID", "Name", "Email");
    print_separator();
}

void print_row(Row* row) {
    printf("| %-30d | %-30s | %-30s |\n", row->id, row->name, row->email);
    print_separator();
}

int main() {
    BTreeNode* root = NULL;

    // Adding rows to the tree
    root = insert(root, new_row(571, "moi", "moi@exemple.com"));
    root = insert(root, new_row(294, "moi-même", "moi-même@exemple.com"));
    root = insert(root, new_row(432, "pasmoi", "pasmoi@exemple.com"));

    // Print all users in the tree
    printf("\n-- All Users in the Database --\n");
    print_header();
    print_tree(root);
    printf("\n");

    // Searching by ID
    int search_id = 571;
    BTreeNode* search_result = search_by_id(root, search_id);
    if (search_result != NULL) {
        printf("\n-- Search by ID (%d) --\n", search_id);
        print_header();
        print_row(search_result->row);
    } else {
        printf("\nNo result found for ID !!!! Try again buddy %d.\n", search_id);
    }

    // Searching by Name
    const char* search_name = "moi";
    search_result = search_by_name(root, search_name);
    if (search_result != NULL) {
        printf("\n-- Search by Name ('%s') --\n", search_name);
        print_header();
        print_row(search_result->row);
    } else {
        printf("\nNo result found for Name '%s'.\n", search_name);
    }

    // Searching by Email
    const char* search_email = "@exemple.com";
    search_result = search_by_email(root, search_email);
    if (search_result != NULL) {
        printf("\n-- Search by Email ('%s') --\n", search_email);
        print_header();
        print_row(search_result->row);
    } else {
        printf("\nNo result found for Email '%s'.\n", search_email);
    }

    // Free tree memory
    free_tree(root);
    return 0;
}



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


