# C School Project - Managing a Binary Tree with SQL

## Description

My name is Balkis( this message is for the teacher )
This project consists of implementing a binary search tree in C to store data from a simulated database using SQL commands (`INSERT`, `SELECT`). The data is stored in a binary file on disk and can be manipulated through various operations.

## Features

- **Inserting records**: Allows insertion of records (rows) with fields like `id`, `name`, and `email`.
- **Searching records**: Provides search functionality to find records by `id`, `name`, or `email`.
- **Persistence**: Saves the binary tree structure to disk and loads it back for later use.
- **In-order traversal**: Displays the records in sorted order based on the `id` field using an in-order traversal of the binary tree.
- **Memory management**: Properly manages memory by freeing allocated space for nodes and rows when done.

## Project Structure

- `src/`: Contains the source code files.
  - `main.c`: Contains the entry point of the program, including the logic for inserting, searching, and displaying records.
  - `btree.c`: Implements the binary tree operations, including insertion, searching, saving, and loading from disk.
  - `table.c`: Contains functions related to managing tables.
  - `row.c`: Manages row data.
  - `repl.c`: Provides a simple REPL for interacting with the database (optional, if implemented).
  
- `Makefile`: A makefile to compile and build the project.
- `database.bin`: The file where the tree structure is saved to disk (persistent storage).


## Compiling
   
   git clone https://github.com/Balkiska/db_c.git

   make run
