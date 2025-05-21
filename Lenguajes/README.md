# Data Dictionary Manager

This project is a **Data Dictionary Manager** implemented in C, designed to create, manage, and interact with custom binary files (`.dat`) that simulate a database-like structure. It allows the user to create **entities**, define **attributes** with types and constraints, and insert **data entries** into those entities, all through a text-based menu interface.

## 📁 Features

- Create and open binary dictionary files.
- Define entities (like tables in databases).
- Add, modify, and delete attributes (with types like `INT`, `FLOAT`, `CHAR`, `STRING`, `BIT`).
- Designate **primary keys**.
- Add data entries to entities.
- View the data dictionary structure, including attributes and stored data.
- Sorted insertion of entities and attributes to maintain an ordered list.

## 🛠️ Technologies Used

- C (Standard I/O, File Handling, Structs)
- Binary file operations for persistent data
- Text-based user interface

## 📌 Data Types Supported

| Type ID | Data Type |
|--------:|-----------|
|   `0`   | BIT (True/False) |
|   `1`   | INTEGER (int) |
|   `2`   | FLOAT (double) |
|   `3`   | CHAR (char) |
|   `4`   | STRING (char array with custom size MAX 50) |

## 🧱 Data Structures

## `ENTITIES`

```c
typedef struct entity {
    char name[LENGTH];
    long listDat;   // Pointer to list of data records
    long listAttr;  // Pointer to list of attributes
    long sig;       // Pointer to next entity
} ENTITIES;
```

## `ATTRIBUTES`

```c
typedef struct attribute {
    char name[LENGTH];
    int isPrimary;  // 1 if it's a primary key
    int type;       // Type ID (BIT, INT, etc.)
    int size;       // Size in bytes
    long next;      // Pointer to next attribute
} ATTRIBUTES;
```

## 📋 How It Works
1. Main Menu

    Create a new .dat dictionary file.

    Open an existing one.

2. Dictionary Menu

    View all entities and their metadata.

    Create/modify/delete/select entities.

    Add data to a selected entity.

3. Entity Menu (after selection)

    View, add, modify, and delete attributes of the selected entity.

4. Data Entry

    Prompts user to enter values for each attribute, based on type.

    Automatically writes data to the end of the binary file and updates the linked list structure.

## 🧑‍💻 How to Compile
Use any C compiler like gcc:
```bash
gcc diccionario.c -o diccionario
```
Then run:
```bash
./diccionario
```
You can also run it in Visual Studio, you just have to press the button "run code".

## 📎 Notes
- All string comparisons are case-insensitive (converted to uppercase).

- Entities and attributes are inserted in sorted order.

- Only one primary key is allowed per entity.

- Data cannot be modified once added, unless the entity is empty.

## 📄 File Format (binary)
The .dat file uses binary structures and offset pointers to simulate linked lists for:

- Entities

- Attributes within each entity

- Data entries for each entity