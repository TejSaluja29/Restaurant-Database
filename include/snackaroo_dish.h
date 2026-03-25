/*
snackaroo_dish.h - header file for snackaroo_dish.c
*/

#ifndef SNACKAROO_DISH_H
#define SNACKAROO_DISH_H

#include <stdio.h>

// max string lengths including null terminator
#define STR_LEN 100

// dish structure for linked list
struct order {
    int code;  // unique, positive integer for the dish
    char name[STR_LEN];  // dish name
    char res_name[STR_LEN];  // restaurant name
    float rating;  // rating out of 10.0
    float price;  // price
    struct order *next;  // pointer to next dish node
};

// global pointer to head of dish linked list
extern struct order *dish_database;

// helper: checks if a dish is contained in the database
struct order* findDish(int code);

// helper: Free all memory in database
void freeDishDatabase();              // free all allocated dish nodes (on quit)

// dish management function declarations
void insertDish(); // add a new dish to the database
void searchDish(); // search for a dish by code and print details
void updateDish(); // update an existing dish
void deleteDish(); // delete a dish by code
void printAllDishes();  // print all dishes in tabular format
void printDish(const struct order *); // print one dish

void dumpDishDatabase(const char *filename);   // save dish list to file using fwrite()
void restoreDishDatabase(const char *filename); // load dish list from file using fread()

#endif
