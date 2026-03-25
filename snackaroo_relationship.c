/*
snackaroo_relationship.c - linked list for dish-driver relationships.
This file manages relationship creation, searching, deletion, printing,
and file persistence for relationship entries.
*/

#include "snackaroo_relationship.h"
#include "snackaroo_dish.h"
#include "snackaroo_driver.h"
#include <stdio.h>
#include <stdlib.h>

struct dish_driver_code *relationship_database = NULL;

// clears unread characters from stdin to avoid input contamination
static void clearLine() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// searches linked list for a relationship matching given relationship ID
struct dish_driver_code* findRelationship(int code) {
    struct dish_driver_code *curr = relationship_database;

    while (curr) {
        if (curr->relationship_ID == code) return curr;
        curr = curr->next;
    }
    return NULL;
}

// frees the entire relationship linked list
void freeRelationshipDatabase() {
    struct dish_driver_code *curr = relationship_database;

    while (curr) {
        struct dish_driver_code *next = curr->next;
        free(curr);
        curr = next;
    }
    relationship_database = NULL;
}

// inserts a new dish-driver relationship
void insertRelation() {
    int dish_code, driver_code, relationship_code;

    // relationship ID input
    for(;;) {
        printf("Enter Relationship Code: ");
        if (scanf(" %d", &relationship_code) != 1) {
            puts("Error: Please enter a valid integer.");
            clearLine();
            continue;
        }
        clearLine();

        if (relationship_code < 0) {
            puts("Error: Code must be non-negative.");
            continue;
        }

        if (findRelationship(relationship_code)) {
            puts("Error: Relationship code already exists.");
            continue;
        }
        break;
    }

    // driver code input
    for(;;) {
        printf("Enter Driver Code: ");
        if (scanf(" %d", &driver_code) != 1) {
            puts("Error: Please enter a valid integer.");
            clearLine();
            continue;
        }
        clearLine();

        if (driver_code < 0) {
            puts("Error: Code must be non-negative.");
            continue;
        }

        if (!findDriver(driver_code)) {
            puts("Error: Driver code doesn't exist.");
            continue;
        }
        break;
    }

    // dish code input
    for(;;) {
        printf("Enter Dish Code: ");
        if (scanf(" %d", &dish_code) != 1) {
            puts("Error: Please enter a valid integer.");
            clearLine();
            continue;
        }
        clearLine();

        if (dish_code < 0) {
            puts("Error: Code must be non-negative.");
            continue;
        }

        if (!findDish(dish_code)) {
            puts("Error: Dish code doesn't exist.");
            continue;
        }
        break;
    }

    // allocate and store relationship node
    struct dish_driver_code *new_relationship = malloc(sizeof(struct dish_driver_code));

    new_relationship->relationship_ID = relationship_code;
    new_relationship->dish_ID = dish_code;
    new_relationship->driver_ID = driver_code;
    new_relationship->next = NULL;

    // add to end of list
    if (!relationship_database) {
        relationship_database = new_relationship;
    } else {
        struct dish_driver_code *curr = relationship_database;
        while (curr->next != NULL) curr = curr->next;
        curr->next = new_relationship;
    }

    puts("Relationship inserted successfully.");
}

// prints a single relationship record
void printRelation(const struct dish_driver_code *o) {
    if (!o) return;

    printf("%-20d %-10d %-10d\n",
        o->relationship_ID, o->dish_ID, o->driver_ID);
}

// prints all dishes linked to a given driver
void printDishRelation() {
    int driver_code;
    int found = 0;

    // validate driver
    for(;;) {
        printf("Enter Driver Code: ");
        if (scanf(" %d", &driver_code) != 1) {
            puts("Error: Please enter a valid integer.");
            clearLine();
            continue;
        }
        clearLine();

        if (driver_code < 0) {
            puts("Error: Code must be non-negative.");
            continue;
        }

        if (!findDriver(driver_code)) {
            puts("Error: Driver doesn't exist.");
            continue;
        }

        break;
    }

    struct dish_driver_code *curr = relationship_database;

    printf("\n%-10s %-25s %-30s %-10s %-10s\n",
        "Code", "Dish Name", "Restaurant", "Rating", "Price");

    // list all dishes delivered by this driver
    while (curr) {
        if (curr->driver_ID == driver_code) {
            struct order *o = findDish(curr->dish_ID);
            if (o) {
                printDish(o);
                found = 1;
            }
        }
        curr = curr->next;
    }

    if (!found) puts("No dishes for this driver.");
}

// prints all drivers linked to a given dish
void printDriverRelation() {
    int dish_code;
    int found = 0;

    // validate dish
    for(;;) {
        printf("Enter Dish Code: ");
        if (scanf(" %d", &dish_code) != 1) {
            puts("Error: Please enter a valid integer.");
            clearLine();
            continue;
        }
        clearLine();

        if (dish_code < 0) {
            puts("Error: Code must be non-negative.");
            continue;
        }

        if (!findDish(dish_code)) {
            puts("Error: Dish doesn't exist.");
            continue;
        }
        break;
    }

    struct dish_driver_code *curr = relationship_database;

    printf("\n%-10s %-25s %-10s %-10s\n",
        "Code", "Name", "Color", "Plate");

    // list all drivers who delivered this dish
    while (curr) {
        if (curr->dish_ID == dish_code) {
            struct driver *d = findDriver(curr->driver_ID);
            if (d) {
                printDriver(d);
                found = 1;
            }
        }
        curr = curr->next;
    }

    if (!found) puts("No drivers for this dish.");
}

// prints all relationship records
void printRelations() {
    if (!relationship_database) {
        puts("No relationships in database.");
        return;
    }

    printf("\n%-20s %-10s %-10s\n",
        "Relationship code", "Dish Code", "Driver Code");

    struct dish_driver_code *curr = relationship_database;

    while (curr) {
        printRelation(curr);
        curr = curr->next;
    }
}

// searches for a specific relationship and prints it
void searchRelation() {
    int relationID;

    printf("Enter Relation Code to Search: ");
    if (scanf(" %d", &relationID) != 1) {
        puts("Error: Invalid input.");
        clearLine();
        return;
    }
    clearLine();

    struct dish_driver_code *relation = findRelationship(relationID);

    if (!relation) {
        puts("Relation not found.");
        return;
    }

    printf("\n%-20s %-10s %-10s\n",
        "Relationship code", "Dish Code", "Driver Code");

    printRelation(relation);
}

// deletes a relationship node from linked list
void deleteRelation() {
    int relationID;

    printf("Enter Relation Code to Delete: ");
    if (scanf(" %d", &relationID) != 1) {
        puts("Error: Invalid input.");
        clearLine();
        return;
    }
    clearLine();

    struct dish_driver_code *curr = relationship_database, *prev = NULL;

    // locate node
    while (curr != NULL && curr->relationship_ID != relationID) {
        prev = curr;
        curr = curr->next;
    }

    if (!curr) {
        puts("Relationship not found.");
        return;
    }

    // unlink node
    if (!prev) {
        relationship_database = curr->next;
    } else {
        prev->next = curr->next;
    }

    free(curr);
    puts("Relation deleted.");
}

// writes all relationship records to a file
void dumpRelationshipDatabase(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        puts("Error: Failed to open file for writing.");
        return;
    }

    struct dish_driver_code *curr = relationship_database;

    while (curr) {
        fwrite(curr, sizeof(struct dish_driver_code), 1, file);
        curr = curr->next;
    }

    fclose(file);
    puts("Relationship database dumped.");
}

// restores relationship records from a file while skipping duplicates 
// and preserving existing list structure by always inserting to the end of the linked list
void restoreRelationshipDatabase(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        puts("Error: Failed to open file for reading.");
        return;
    }

    struct dish_driver_code temp;

    while (fread(&temp, sizeof(struct dish_driver_code), 1, file)) {

        if (findRelationship(temp.relationship_ID)) {
            printf("\nRelation ID %d already exists in database", temp.relationship_ID);
            continue;
        }

        if (!findDish(temp.dish_ID)) {
            printf("\ndish for driver ID %d in Relationship %d no longer exists",
                temp.driver_ID, temp.relationship_ID);
            continue;
        }

        if (!findDriver(temp.driver_ID)) {
            printf("\ndriver for dish ID %d in Relationship %d no longer exists",
                temp.dish_ID, temp.relationship_ID);
            continue;
        }

        struct dish_driver_code *new_relation = malloc(sizeof(struct dish_driver_code));
        *new_relation = temp;
        new_relation->next = NULL;

        if (!relationship_database) {
            relationship_database = new_relation;
        } else {
            struct dish_driver_code *curr = relationship_database;
            while (curr->next) curr = curr->next;
            curr->next = new_relation;
        }
    }

    fclose(file);
    puts("\nRelationship database restored");
}
