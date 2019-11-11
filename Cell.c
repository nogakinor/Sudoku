#include "string.h"

#ifndef CELL
#define CELL

/*
this module represents the cell and indicates its value and whether the cell is fixed or not
*/
typedef struct soduCell {
    int value;
    char isFixed;
} sudoCell;

#endif
