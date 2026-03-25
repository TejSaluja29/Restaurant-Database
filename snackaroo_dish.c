/*
snackaroo_dish.c - linked list for dish records. This file handles
input validation, dynamic allocation, searching, updating, deletion, printing,
and file persistence for dish entries.
*/

#include "snackaroo_dish.h"
#include "snackaroo_relationship.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct order *dish_database = NULL;

// clears unread characters from stdin to avoid input contamination
static void clearLine() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// checks if a dish is referenced in any dish-driver relationship
static int checkDishRel(struct order *dish) {
    int dish_code = dish->code;

    struct dish_driver_code *curr = relationship_database;
    while (curr) {
        if (curr->dish_ID == dish_code) return 1;
        curr = curr->next;
    }
    return 0;
}

// searches linked list for a dish matching the given code
struct order* findDish(int code) {
    struct order *curr = dish_database;
    while (curr) {
        if (curr->code == code) return curr;
        curr = curr->next;
    }
    return NULL;
}

// frees the entire dish linked list
void freeDishDatabase() {
    struct order *curr = dish_database;
    while (curr) {
        struct order *next = curr->next;
        free(curr);
        curr = next;
    }
    dish_database = NULL;
}

// inserts a new dish into the linked list
void insertDish() {
    int code;
    char name[STR_LEN];
    char res_name[STR_LEN];
    float rating, price;

    // obtain a unique dish code
    // ensures non-negative value and no duplicates in list
    for(;;) {
        printf("Enter Dish Code: ");
        if (scanf(" %d", &code) != 1) {
            puts("Error: Please enter a valid integer.");
            clearLine();
            continue;
        }
        clearLine();

        if (code < 0) {
            puts("Error: Code must be non-negative.");
            continue;
        }
        if (findDish(code)) {
            puts("Error: Code already exists in database.");
            continue;
        }
        break;
    }

    // reads dish name
    for(;;) {
        printf("Enter Dish Name: ");
        if (!fgets(name, sizeof(name), stdin)) return;
        size_t len = strcspn(name, "\n");
        if (name[len] == '\n') name[len] = '\0';
        else {
            clearLine();
            puts("Error: name too long, kept first 99 characters.");
        }
        break;
    }

    // reads restaurant name
    for(;;) {
        printf("Enter Restaurant Name: ");
        if (!fgets(res_name, sizeof(res_name), stdin)) return;
        size_t len = strcspn(res_name, "\n");
        if (res_name[len] == '\n') res_name[len] = '\0';
        else {
            clearLine();
            puts("Error: name too long, kept first 99 characters.");
        }
        break;
    }

    // rating input validation ensures range 0.0 to 10.0
    for(;;) {
        printf("Enter Dish Rating (0.0 - 10.0): ");
        if (scanf(" %f", &rating) != 1) {
            puts("Error: Please enter a valid float.");
            clearLine();
            continue;
        }
        clearLine();
        if (rating < 0.0f || rating > 10.0f) {
            puts("Error: Rating must be between 0.0 and 10.0.");
            continue;
        }
        break;
    }

    // price must be positive float
    for(;;) {
        printf("Enter Price: ");
        if (scanf(" %f", &price) != 1) {
            puts("Error: Please enter a valid float.");
            clearLine();
            continue;
        }
        clearLine();
        if (price < 0.0f) {
            puts("Error: Price must be a positive float.");
            continue;
        }
        break;
    }

    // allocates a new node and stores the validated input
    struct order *new_dish = malloc(sizeof(struct order));

    new_dish->code = code;
    strncpy(new_dish->name, name, STR_LEN);
    strncpy(new_dish->res_name, res_name, STR_LEN);
    new_dish->rating = rating;
    new_dish->price = price;
    new_dish->next = NULL;

    // appends node to end of list to preserve insertion order
    if (!dish_database) {
        dish_database = new_dish;
    } else {
        struct order *curr = dish_database;
        while (curr->next != NULL) curr = curr->next;
        curr->next = new_dish;
    }

    puts("Dish inserted successfully.");
}

// prints a single dish record using formatted layout
void printDish(const struct order *o) {
    if (!o) return;

    printf("%-10d %-25.25s %-30.30s %-10.1f $%-10.2f\n",
        o->code, o->name, o->res_name, o->rating, o->price);
}

// prints all dish records by traversing linked list
void printAllDishes() {
    if (!dish_database) {
        puts("No dishes in database.");
        return;
    }

    printf("\n%-10s %-25s %-30s %-10s %-10s\n",
        "Code", "Dish Name", "Restaurant", "Rating", "Price");

    struct order *curr = dish_database;
    while (curr) {
        printDish(curr);
        curr = curr->next;
    }
}

// searches for dish code and prints record if found
void searchDish() {
    int code;

    printf("Enter Dish Code to Search: ");
    if (scanf(" %d", &code) != 1) {
        puts("Error: Invalid input.");
        clearLine();
        return;
    }
    clearLine();

    struct order *found = findDish(code);

    if (!found) {
        puts("Dish not found.");
        return;
    }

    printf("\n%-10s %-25s %-30s %-10s %-10s\n",
        "Code", "Dish Name", "Restaurant", "Rating", "Price");
    printDish(found);
}

// updates a dish in-place by modifying an existing node
void updateDish() {
    int code;

    printf("Enter Dish Code to Update: ");
    if (scanf(" %d", &code) != 1) {
        puts("Error: Invalid input.");
        clearLine();
        return;
    }
    clearLine();

    struct order *dish = findDish(code);

    if (!dish) {
        puts("Dish not found.");
        return;
    }

    char name[STR_LEN];
    char res_name[STR_LEN];
    float rating, price;

    // input new dish name
    for(;;) {
        printf("Enter New Dish Name: ");
        if (!fgets(name, sizeof(name), stdin)) return;
        size_t len = strcspn(name, "\n");
        if (name[len] == '\n') name[len] = '\0';
        else {
            clearLine();
            puts("Error: name too long, kept first 99 characters.");
        }
        break;
    }

    // input new restaurant name
    for(;;) {
        printf("Enter New Restaurant Name: ");
        if (!fgets(res_name, sizeof(res_name), stdin)) return;
        size_t len = strcspn(res_name, "\n");
        if (res_name[len] == '\n') res_name[len] = '\0';
        else {
            clearLine();
            puts("Error: name too long, kept first 99 characters.");
        }
        break;
    }

    // input new rating
    for(;;) {
        printf("Enter New Rating (0.0 - 10.0): ");
        if (scanf(" %f", &rating) != 1) {
            puts("Error: Please enter a valid float.");
            clearLine();
            continue;
        }
        clearLine();

        if (rating < 0.0f || rating > 10.0f) {
            puts("Error: Rating must be between 0.0 and 10.0.");
            continue;
        }
        break;
    }

    // input new price
    for(;;) {
        printf("Enter New Price: ");
        if (scanf(" %f", &price) != 1) {
            puts("Error: Please enter a valid float.");
            clearLine();
            continue;
        }
        clearLine();

        if (price < 0.0f) {
            puts("Error: Price must be a positive float.");
            continue;
        }
        break;
    }

    // modify record
    strncpy(dish->name, name, STR_LEN);
    strncpy(dish->res_name, res_name, STR_LEN);
    dish->rating = rating;
    dish->price = price;

    puts("Dish updated.");
}

// deletes a dish node from linked list and checks for referential integrity before deletion
void deleteDish() {
    int code;

    printf("Enter Dish Code to Delete: ");
    if (scanf(" %d", &code) != 1) {
        puts("Error: Invalid input.");
        clearLine();
        return;
    }
    clearLine();

    struct order *curr = dish_database, *prev = NULL;

    // locate node
    while (curr != NULL && curr->code != code) {
        prev = curr;
        curr = curr->next;
    }

    if (!curr) {
        puts("Dish not found.");
        return;
    }

    // prevent deletion if referenced in relationships
    if (checkDishRel(curr)) {
        puts("Cannot delete this dish since it is referenced in relationship database.");
        return;
    }

    // unlink node
    if (!prev) {
        dish_database = curr->next;
    } else {
        prev->next = curr->next;
    }

    free(curr);
    puts("Dish deleted.");
}

// writes all dish records to a file
void dumpDishDatabase(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        puts("Error: Failed to open file for writing.");
        return;
    }

    struct order *curr = dish_database;
    while (curr) {
        fwrite(curr, sizeof(struct order), 1, file);
        curr = curr->next;
    }

    fclose(file);
    puts("Dish database dumped.");
}

// restores dish records from a file while skipping duplicates and preserving existing list structure 
// by always inserting to the end of the linked list
void restoreDishDatabase(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        puts("Error: Failed to open file for reading.");
        return;
    }

    struct order temp;

    while (fread(&temp, sizeof(struct order), 1, file)) {

        if (findDish(temp.code)) {
            printf("\nDish with code %d already exists in database", temp.code);
            continue;
        }

        struct order *new_dish = malloc(sizeof(struct order));
        if (!new_dish) break;

        *new_dish = temp;
        new_dish->next = NULL;

        if (!dish_database) {
            dish_database = new_dish;
        } else {
            struct order *curr = dish_database;
            while (curr->next) curr = curr->next;
            curr->next = new_dish;
        }
    }

    fclose(file);
    puts("\nDish database restored.");
}
