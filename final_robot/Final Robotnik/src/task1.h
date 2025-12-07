#ifndef TASK1_H
#define TASK_H

#include <Arduino.h>

// Dimensions (9 lines = indices 0 to 8)
#define GRID_SIZE 9 

// Directions
#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3

// Node States
#define UNKNOWN  0
#define EMPTY    1
#define OBSTACLE 2
#define BOX      3  
#define VISITED  4

int objectIdentify(char direction);
int Task1();

#endif