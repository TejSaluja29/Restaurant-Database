/*
snackaroo_relationship.h - header file for snackaroo_relationship.c
*/

#ifndef SNACKAROO_RELATIONSHIP_H
#define SNACKAROO_RELATIONSHIP_H


#include <stdio.h>

struct dish_driver_code {
    int relationship_ID; // unique, relationship ID
    int dish_ID;  // dish code already existing in the dish database
    int driver_ID; // driver code already existing in the driver database;
    struct dish_driver_code *next;
};

// global pointer to head of relationship linked list
extern struct dish_driver_code *relationship_database;

// helper: checks if a relation is contained in the database
struct dish_driver_code* findRelationship(int code);

// helper: free all allocated memory on exit
void freeRelationshipDatabase();

void insertRelation(); // Add new dish/driver relationship
void searchRelation();  // Find relationship by code and print details
void deleteRelation(); // Delete dish/driver relationship
void printRelations();  // Print all relationships
void printDishRelation(); // Prints all the dishes associated with a certain driver
void printDriverRelation(); // Prints all the drivers associated with a certain dish
void printRelation(const struct dish_driver_code *); // Print one relationship (helper)

// Bonus: File I/O for persistence
void dumpRelationshipDatabase(const char *filename);    // Save driver list to file
void restoreRelationshipDatabase(const char *filename); // Load driver list from file


#endif