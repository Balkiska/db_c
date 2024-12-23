#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include "table.h"
#include "btree.c"


typedef enum {
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum { PREPARE_SUCCESS, PREPARE_UNRECOGNIZED_STATEMENT } PrepareResult;

typedef enum { STATEMENT_INSERT, STATEMENT_SELECT } StatementType;

typedef struct {
    StatementType type;
    char* data;
} Statement;

// buffer management 
typedef struct {
  char* buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;


InputBuffer* new_input_buffer() {
  InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;

  return input_buffer;
}


void print_prompt() { 
  printf("db > "); 
}


void read_input(InputBuffer* input_buffer) {
  ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
  
  if (bytes_read <= 0) {
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }
  
  // Ignore trailing newline
  input_buffer->input_length = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = 0; 
}

void close_input_buffer(InputBuffer* input_buffer) {
  free(input_buffer->buffer);
  free(input_buffer);
}

// Order processing '.'
MetaCommandResult do_meta_command(InputBuffer* input_buffer) {
    if (strcmp(input_buffer->buffer, ".exit") == 0) {
        close_input_buffer(input_buffer);
        exit(EXIT_SUCCESS);
    }
    // Backup database
    if (strcmp(input_buffer->buffer, ".backup") == 0) {
        backup_database();
        return META_COMMAND_SUCCESS;
    }
    return META_COMMAND_UNRECOGNIZED_COMMAND;
}

// Preparation of the statement
PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        statement->data = strdup(input_buffer->buffer + 7);
        return PREPARE_SUCCESS;
    }
    if (strcmp(input_buffer->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
    return PREPARE_UNRECOGNIZED_STATEMENT;
}

//INSERT
void execute_insert(Statement* statement) {
    printf("Insert command with data: %s\n", statement->data);
    Row* row = (Row*)malloc(sizeof(Row)); 
    row->id = 666; 
    row->name = statement->data; 
    root = insert(root, row); 
}

//SELECT
void execute_select() {
    printf("Executing SELECT command...\n");
    BTreeNode* result = search_by_id(root, 666); 
    if (result != NULL) {
        printf("Found row: %s\n", result->row->name);
    } else {
        printf("Row not found !!!!!!!\n");
    }
}

// Executes the instruction according to its type
void execute_statement(Statement* statement) {
  switch (statement->type) {
    case (STATEMENT_INSERT):
      execute_insert(statement);
      break;
    case (STATEMENT_SELECT):
      execute_select();
      break;
  }
}

//REPL loop
void repl(void) {
  InputBuffer* input_buffer = new_input_buffer();
  
  while (true) {
    print_prompt();
    read_input(input_buffer);
    
    if (input_buffer->buffer[0] == '.') {
      switch (do_meta_command(input_buffer)) {
        case (META_COMMAND_SUCCESS):
          continue;
        case (META_COMMAND_UNRECOGNIZED_COMMAND):
          printf("Unrecognized command... '%s'\n", input_buffer->buffer);
          continue;
      }
    }
    
    Statement statement;
    switch (prepare_statement(input_buffer, &statement)) {
      case (PREPARE_SUCCESS):
        break;
      case (PREPARE_UNRECOGNIZED_STATEMENT):
        printf("Unrecognized keyword at start of '%s'.\n", input_buffer->buffer);
        continue;
    }
    
    execute_statement(&statement);
    printf("Executed.\n");
  }
}

