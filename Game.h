

#ifndef UNTITLED_GAME_H
#define UNTITLED_GAME_H

#include "Parser.h"
#include "Solver.h"

int printBoard(sudoCell board[9][9]);
int setCell(sudoCell playerBoard[9][9], int row, int col, int num, int* progress);
int begin(sudoCell ptr[9][9], sudoCell playerBoard[9][9], int* progress);
int init();

#endif

