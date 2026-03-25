/*
snackaroo.c - main program for handling user menus, dish management,
driver management, and dish-driver relationship operations.
*/

#include "snackaroo.h"
#include "snackaroo_dish.h"
#include "snackaroo_driver.h"
#include "snackaroo_relationship.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void clearLine() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// prints main menu
void menu() {
    fflush(stdout);
    char *str = "   Snackaroo App   ";

    printf("\n");
    for (int i = 0; i <= (int) strlen(str) + 1; i++) printf("*");
    printf("\n*%s*\n", str);                                        
    for (int i = 0; i <= (int) strlen(str) + 1; i++) printf("*");   

    // menu items
    printf("\n\nOperation codes: \n"
        "\nShow help menu: 'h'"
        "\nQuit the program: 'q'"
        "\nManage dishes: 'm'"
        "\nManage drivers: 'a'"
        "\nManage dish-driver relationship: 'r'\n");
}

// dish operations submenu
void dishMenu() {
    char cmd;

    // menu options
    printf("\nDish Menu:\n");
    printf("Insert new dish: 'i'\n");
    printf("Search for dish by code: 's'\n");
    printf("Update existing dish: 'u'\n");
    printf("Erase dish: 'e'\n");
    printf("Print all dishes: 'p'\n");
    printf("Dump dishes to file: 'd'\n");
    printf("Restore dishes from file: 'r'\n");
    printf("Exit to main menu: 'x'\n");

    for(;;) {
        printf("\nEnter operation code: ");

        if (scanf(" %c", &cmd) != 1) break;
        clearLine();

        switch (cmd) {
            case 'i': insertDish(); break;           // insert new dish
            case 's': searchDish(); break;           // search dish
            case 'u': updateDish(); break;           // update dish
            case 'e': deleteDish(); break;           // delete dish
            case 'p': printAllDishes(); break;       // print list
            case 'd': { // dump/save into file
                char filename[100];
                printf("Enter file to dump to: ");
                scanf(" %99s", filename);
                getchar();
                dumpDishDatabase(filename);
                break;
            }
            case 'r': { // restore from file
                char filename[100];
                printf("Enter file to restore from: ");
                scanf(" %99s", filename);
                getchar();
                restoreDishDatabase(filename);
                break;
            }
            case 'x': return; // return to main menu
            default: printf("Invalid dish command.\n");
        }
    }
}

// driver operations submenu
void driverMenu() {
    char cmd;

    // menu options
    printf("\nDriver Menu:\n");
    printf("Insert new driver: 'i'\n");
    printf("Search for driver by code: 's'\n");
    printf("Update existing driver: 'u'\n");
    printf("Erase driver: 'e'\n");
    printf("Print all drivers: 'p'\n");
    printf("Dump drivers to file: 'd'\n");
    printf("Restore drivers from file: 'r'\n");
    printf("Exit to main menu: 'x'\n");

    for(;;) {
        printf("\nEnter operation code: ");

        if (scanf(" %c", &cmd) != 1) break;
        clearLine();

        switch (cmd) {
            case 'i': insertDriver(); break;         // insert
            case 's': searchDriver(); break;         // search
            case 'u': updateDriver(); break;         // update
            case 'e': deleteDriver(); break;         // delete
            case 'p': printAllDrivers(); break;      // print list
            case 'd': { // dump/save into file
                char filename[100];
                printf("Enter file to dump to: ");
                scanf(" %99s", filename);
                getchar();
                dumpDriverDatabase(filename);
                break;
            }
            case 'r': { // restore from file
                char filename[100];
                printf("Enter file to restore from: ");
                scanf(" %99s", filename);
                getchar();
                restoreDriverDatabase(filename);
                break;
            }
            case 'x': return; // return to main menu
            default: printf("Invalid driver command.\n");
        }
    }
}

// relationship operations submenu
void relationshipMenu() {
    char cmd;

    // menu options
    printf("\nRelationship Menu:\n");
    printf("Insert dish-driver relationship: 'i'\n");
    printf("Search and print all relationships: 's'\n");
    printf("Erase relationship: 'e'\n");
    printf("Print all relations: 'p'\n");
    printf("Print all dishes for a driver: 'f'\n");
    printf("Print all drivers for a dish: 'g'\n");
    printf("Dump relationships to file: 'd'\n");
    printf("Restore relationships from file: 'r'\n");
    printf("Exit to main menu: 'x'\n");

    for(;;) {
        printf("\nEnter operation code: ");

        if (scanf(" %c", &cmd) != 1) break;
        clearLine();

        switch (cmd) {
            case 'i': insertRelation(); break; // insert
            case 's': searchRelation(); break; // search
            case 'e': deleteRelation(); break; // erase
            case 'p': printRelations(); break; // print
            case 'f': printDishRelation(); break; // print by dish
            case 'g': printDriverRelation(); break; // print by driver
            case 'd': { // dump/save into file
                char filename[100];
                printf("Enter file to dump to: ");
                scanf(" %99s", filename);
                getchar();
                dumpRelationshipDatabase(filename);
                break;
            }
            case 'r': { // restore from file
                char filename[100];
                printf("Enter file to restore from: ");
                scanf(" %99s", filename);
                getchar();
                restoreRelationshipDatabase(filename);
                break;
            }
            case 'x': return; // return to main menu
            default: printf("Invalid relationship command.\n");
        }
    }
}

int main() {
    char command;

    menu();     // initial menu

    for(;;) {
        printf("\nMain Command (h for help): ");

        if (scanf(" %c", &command) != 1) break;
        clearLine();

        switch (command) {
            case 'h': menu(); break;            // help
            case 'q':                           // quit program
                printf("Exiting Snackaroo. Goodbye!\n");
                freeDishDatabase();
                freeDriverDatabase();
                freeRelationshipDatabase();
                return 0;

            case 'm': dishMenu(); break;        // dish submenu
            case 'a': driverMenu(); break;      // driver submenu
            case 'r': relationshipMenu(); break;// relation submenu
            default: printf("Invalid command.\n");
        }
    }

    return 0;
}
