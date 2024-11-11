#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "table.h"

// Enum to define different types of statements
typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

// Enum to define preparation result of statement
typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

// Enum to define statement types like INSERT and SELECT
typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

// Struct to store information about a statement, including data for INSERT
typedef struct {
    StatementType type;
    int id;
    char name[666]; 
} Statement;

// Function to prepare the statement based on user input
PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
    // Check if the command starts with "insert"
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;

        // Parse the input to extract ID and name in the format "insert <id> <name>"
        int assigned = sscanf(input_buffer->buffer, "insert %d %s", &(statement->id), statement->name);
        if (assigned < 2) {  // Error if parsing failed
            return PREPARE_UNRECOGNIZED_STATEMENT;
        }
        return PREPARE_SUCCESS;
    }
    
    // Check if the command is "select"
    if (strcmp(input_buffer->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}

// Function to execute the prepared statement
void execute_statement(Statement* statement) {
    switch (statement->type) {
        case (STATEMENT_INSERT):
            // Call table_insert to insert a row into the table
            if (table_insert(statement->id, statement->name)) {
                printf("Executed INSERT.\n");
            } else {
                printf("Failed to execute INSERT.\n");
            }
            break;
            
        case (STATEMENT_SELECT):
            // Call table_select to display all rows in the table
            table_select();
            break;
    }
}
