/*
snackaroo_driver.c - linked list for driver records. This file handles
input validation, dynamic allocation, searching, updating, deletion, printing,
and file persistence for driver entries.
*/

#include "snackaroo_driver.h"
#include "snackaroo_relationship.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct driver *driver_database = NULL;

// clears unread characters from stdin to avoid input contamination
static void clearLine() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// checks if a driver is referenced in any dish-driver relationship
static int checkDriverRel(struct driver *driver) {
    int driver_code = driver->code;

    struct dish_driver_code *curr = relationship_database;
    while (curr) {
        if (curr->driver_ID == driver_code) return 1;
        curr = curr->next;
    }
    return 0;
}

// searches linked list for a driver matching the given code
struct driver* findDriver(int code) {
    struct driver *curr = driver_database;
    while (curr) {
        if (curr->code == code) return curr;
        curr = curr->next;
    }
    return NULL;
}

// frees the entire driver linked list
void freeDriverDatabase() {
    struct driver *curr = driver_database;
    while (curr) {
        struct driver *next = curr->next;
        free(curr);
        curr = next;
    }
    driver_database = NULL;
}

// validates license plate format
static int isValidPlate(const char *plate) {
    size_t len = strlen(plate);
    if (len < 2 || len > 8) return 0;

    for (size_t i = 0; i < len; i++) {
        if (!isalnum(plate[i]) && plate[i] != ' ') return 0;
    }
    return 1;
}

// inserts a new driver into the linked list
void insertDriver() {
    int code;
    char name[DRIVER_NAME_LEN];
    int color;
    char plate[PLATE_LEN];

    // obtain a unique driver code
    for(;;) {
        printf("Enter Driver Code: ");
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
        if (findDriver(code)) {
            puts("Error: Driver code already exists.");
            continue;
        }
        break;
    }

    // reads driver name
    for(;;) {
        printf("Enter Driver Name: ");
        if (!fgets(name, sizeof(name), stdin)) return;
        size_t len = strcspn(name, "\n");
        if (name[len] == '\n') name[len] = '\0';
        else {
            clearLine();
            puts("Error: name too long, kept first 49 characters.");
        }
        break;
    }

    // vehicle color selection
    for(;;) {
        printf("0=red\n1=green\n2=blue\n3=grey\n4=white\n5=black\n6=other\nEnter Vehicle Color: ");
        if (scanf(" %d", &color) != 1) {
            puts("Error: Please enter an integer.");
            clearLine();
            continue;
        }
        clearLine();

        if (color < 0 || color > 6) {
            puts("Error: Color must be between 0 and 6.");
            continue;
        }
        break;
    }

    // license plate input
    for(;;) {
        printf("Enter License Plate (2-8 alphanumeric characters or space): ");
        if (!scanf(" %s", plate)) return;
        clearLine();

        if (!isValidPlate(plate)) {
            puts("Error: Invalid license plate format.");
            continue;
        }
        break;
    }

    // allocate and store driver node
    struct driver *new_driver = malloc(sizeof(struct driver));

    new_driver->code = code;
    strncpy(new_driver->name, name, DRIVER_NAME_LEN);
    new_driver->vehicle_color = color;
    strncpy(new_driver->license_plate, plate, PLATE_LEN);
    new_driver->next = NULL;

    // add to end of list
    if (!driver_database) {
        driver_database = new_driver;
    } else {
        struct driver *curr = driver_database;
        while (curr->next) curr = curr->next;
        curr->next = new_driver;
    }

    puts("Driver inserted successfully.");
}

// prints a single driver record using formatted layout
void printDriver(const struct driver *d) {
    if (!d) return;

    const char *colors[] = {"red", "green", "blue", "grey", "white", "black", "other"};

    printf("%-10d %-25.25s %-10s %-10s\n",
        d->code, d->name,
        (d->vehicle_color >= 0 && d->vehicle_color <= 6) ? colors[d->vehicle_color] : "invalid",
        d->license_plate);
}

// prints all driver records
void printAllDrivers() {
    if (!driver_database) {
        puts("No drivers in database.");
        return;
    }

    printf("\n%-10s %-25s %-10s %-10s\n",
        "Code", "Name", "Color", "Plate");

    struct driver *curr = driver_database;
    while (curr) {
        printDriver(curr);
        curr = curr->next;
    }
}

// searches for driver code and prints record if found
void searchDriver() {
    int code;

    printf("Enter Driver Code to Search: ");
    if (scanf(" %d", &code) != 1) {
        puts("Error: Invalid input.");
        clearLine();
        return;
    }
    clearLine();

    struct driver *d = findDriver(code);

    if (!d) {
        puts("Driver not found.");
        return;
    }

    printf("\n%-10s %-25s %-10s %-10s\n",
        "Code", "Name", "Color", "Plate");
    printDriver(d);
}

// updates a driver in-place
void updateDriver() {
    int code;
    char name[DRIVER_NAME_LEN];
    int color;
    char plate[PLATE_LEN];

    printf("Enter Driver Code to Update: ");
    if (scanf(" %d", &code) != 1) {
        puts("Error: Invalid input.");
        clearLine();
        return;
    }
    clearLine();

    struct driver *d = findDriver(code);

    if (!d) {
        puts("Driver not found.");
        return;
    }

    // new name
    for(;;) {
        printf("Enter New Name: ");
        if (!fgets(name, sizeof(name), stdin)) return;
        size_t len = strcspn(name, "\n");
        if (name[len] == '\n') name[len] = '\0';
        else {
            clearLine();
            puts("Error: name too long.");
        }
        break;
    }

    // new vehicle color
    for(;;) {
        printf("Enter New Vehicle Color (0-6): ");
        if (scanf(" %d", &color) != 1) {
            puts("Error: enter an integer.");
            clearLine();
            continue;
        }
        clearLine();

        if (color < 0 || color > 6) {
            puts("Error: Invalid color value.");
            continue;
        }
        break;
    }

    // new license plate
    for(;;) {
        printf("Enter License Plate (2-8 alphanumeric or space): ");
        if (!scanf(" %s", plate)) return;
        clearLine();

        if (!isValidPlate(plate)) {
            puts("Error: Invalid license plate format.");
            continue;
        }
        break;
    }

    // update record
    strncpy(d->name, name, DRIVER_NAME_LEN);
    d->vehicle_color = color;
    strncpy(d->license_plate, plate, PLATE_LEN);

    puts("Driver updated.");
}

// deletes a driver node and checks for referential integrity before deletion
void deleteDriver() {
    int code;

    printf("Enter Driver Code to Delete: ");
    if (scanf(" %d", &code) != 1) {
        puts("Error: Invalid input.");
        clearLine();
        return;
    }
    clearLine();

    struct driver *curr = driver_database, *prev = NULL;

    // locate node
    while (curr != NULL && curr->code != code) {
        prev = curr;
        curr = curr->next;
    }

    if (!curr) {
        puts("Driver not found.");
        return;
    }

    if (checkDriverRel(curr)) {
        puts("Cannot delete driver due to existing relationship link.");
        return;
    }

    // unlink node
    if (!prev) {
        driver_database = curr->next;
    } else {
        prev->next = curr->next;
    }

    free(curr);
    puts("Driver deleted.");
}

// writes all driver records to a file
void dumpDriverDatabase(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        puts("Error: Could not open file for writing.");
        return;
    }

    struct driver *curr = driver_database;

    while (curr) {
        fwrite(curr, sizeof(struct driver), 1, file);
        curr = curr->next;
    }

    fclose(file);
    puts("Driver database dumped.");
}

// restores driver records from a file while skipping duplicates
void restoreDriverDatabase(const char *filename) {
    FILE *file = fopen(filename, "rb");

    if (!file) {
        puts("Error: Could not open file for reading.");
        return;
    }

    struct driver temp;

    while (fread(&temp, sizeof(struct driver), 1, file)) {

        if (findDriver(temp.code)) {
            printf("\nDriver with code %d already exists in database", temp.code);
            continue;
        }

        struct driver *new_driver = malloc(sizeof(struct driver));
        if (!new_driver) break;

        *new_driver = temp;
        new_driver->next = NULL;

        if (!driver_database) {
            driver_database = new_driver;
        } else {
            struct driver *curr = driver_database;
            while (curr->next) curr = curr->next;
            curr->next = new_driver;
        }
    }

    fclose(file);
    puts("\nDriver database restored");
}
