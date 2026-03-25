/*
snackaroo_driver.h - header file for snackaroo_driver.c
*/

#ifndef SNACKAROO_DRIVER_H
#define SNACKAROO_DRIVER_H

#include <stdio.h>

// Max string lengths (including \0)
#define DRIVER_NAME_LEN 50
#define PLATE_LEN 9

// vehicle color codes
#define COLOR_RED     0
#define COLOR_GREEN   1
#define COLOR_BLUE    2
#define COLOR_GREY    3
#define COLOR_WHITE   4
#define COLOR_BLACK   5
#define COLOR_OTHER   6

// driver structure for linked list
struct driver {
    int code;   // unique, driver ID
    char name[DRIVER_NAME_LEN];  // driver name (max 49 + '\0')
    int vehicle_color;    // integer 0–6 representing vehicle color
    char license_plate[PLATE_LEN];  // 2–8 character alphanumeric plate
    struct driver *next;   // pointer to next node
};

// global pointer to head of driver linked list
extern struct driver *driver_database;

// helper: checks if a driver is contained in the database
struct driver* findDriver(int code);

// helper: free all memory in database
void freeDriverDatabase();

// driver management function declarations
void insertDriver(); // Add new driver
void searchDriver();  // Find driver by code and print details
void updateDriver(); // Update existing driver
void deleteDriver(); // Delete driver by code
void printAllDrivers();  // Print all drivers
void printDriver(const struct driver *); // Print one driver (helper)

void dumpDriverDatabase(const char *filename);    // Save driver list to file
void restoreDriverDatabase(const char *filename); // Load driver list from file

#endif