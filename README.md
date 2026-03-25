# Restaurant Database in C

![Language](https://img.shields.io/badge/Language-C-00599C)
![Build](https://img.shields.io/badge/Build-GCC%20%2B%20Make-success)
![Data Structures](https://img.shields.io/badge/Data%20Structures-Linked%20Lists-orange)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen)

## Overview

This project is a modular, menu-driven database application written in C. It manages three connected datasets:

- dishes
- drivers
- dish-to-driver relationships

The system stores records in linked lists, supports CRUD-style operations through a command-line interface, and includes binary file persistence for saving and restoring data between sessions.

Beyond the feature set itself, this project was a strong exercise in core systems programming concepts such as pointers, dynamic memory management, input validation, modular design, and manual data structure implementation.

## Why This Project Matters

This repository highlights hands-on experience with low-level programming fundamentals rather than relying on higher-level frameworks or database libraries.

It helped me learn the basics of C by implementing linked lists to create a lightweight database in C, while also reinforcing how to:

- structure a multi-file C project cleanly
- manage memory manually with `malloc` and `free`
- validate user input in a console application
- enforce simple referential integrity across related records
- serialize in-memory data to binary files with `fwrite` and `fread`

## Core Features

- Create, search, update, delete, and print dish records
- Create, search, update, delete, and print driver records
- Create and manage relationships between dishes and drivers
- Prevent deletion of records that are still referenced by relationships
- Save each database module to disk and restore it later
- Navigate the system through a command-based terminal menu

## Technical Highlights

- Language: C
- Build tooling: GCC + Make
- Data model: singly linked lists
- Storage approach: in-memory records with binary file export/import
- Program structure: separated into domain-specific modules for dishes, drivers, and relationships

## Project Structure

```text
/
|-- README.md
|-- makefile
|-- .gitignore
|-- include/
|   |-- snackaroo.h
|   |-- snackaroo_dish.h
|   |-- snackaroo_driver.h
|   `-- snackaroo_relationship.h
|-- src/
|   |-- snackaroo.c
|   |-- snackaroo_dish.c
|   |-- snackaroo_driver.c
|   `-- snackaroo_relationship.c
|-- data/
|   `-- .gitkeep
|-- build/
|   `-- .gitkeep
`-- bin/
    `-- .gitkeep
```

`build/` and `bin/` are reserved for generated artifacts and are ignored by Git.  
`data/` is available for exported database files created by the program.

## Architecture

### `snackaroo.c`

Application entry point and menu navigation.

### `snackaroo_dish.c`

Handles dish records, including validation, linked-list insertion, updates, deletion, printing, and file persistence.

### `snackaroo_driver.c`

Handles driver records, including vehicle metadata, validation, linked-list operations, and persistence.

### `snackaroo_relationship.c`

Manages relationships between dishes and drivers and ensures linked records exist before relationships are created or restored.

## How to Build

If you have `make` available:

```bash
make
```

If you are using a Windows MinGW setup, you may need:

```bash
mingw32-make
```

## How to Run

After building, run:

```powershell
.\bin\snackaroo.exe
```

## Manual Compile Option

If you prefer to compile without `make`, use:

```bash
gcc -Wall -Wextra -std=c11 -Iinclude src/snackaroo.c src/snackaroo_dish.c src/snackaroo_driver.c src/snackaroo_relationship.c -o bin/snackaroo.exe
```

## What This Demonstrates

This project demonstrates practical experience with:

- linked lists and pointer manipulation
- modular C development with header/source separation
- user input handling in terminal-based programs
- binary file I/O
- memory cleanup and lifecycle management
- maintaining relationships between interconnected records

## Future Improvements

- replace linear search with more efficient indexing structures
- add automated tests for validation and persistence logic
- support text-based export formats such as CSV
- introduce clearer error reporting and more robust recovery paths

## Final Note

This is a compact project, but it reflects the kind of foundational work that builds strong C programming instincts: understanding how data is stored, connected, validated, persisted, and cleaned up without the abstractions of higher-level tools.
