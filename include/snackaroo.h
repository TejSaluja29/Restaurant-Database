/*
snackaroo.h - header file for snackaroo.c
*/

#ifndef SNACKAROO_H
#define SNACKAROO_H

#include <stdio.h>

void menu();  // Displays main menu commands: h, q, m, a, r

void dishMenu();       // Handles commands for managing dishes
void driverMenu();     // Handles commands for managing drivers
void relationshipMenu(); // Handles dish-driver link menu

#endif