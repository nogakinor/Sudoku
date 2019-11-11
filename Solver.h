
#ifndef UNTITLED_SOLVER_H
#define UNTITLED_SOLVER_H
#include <stdlib.h>
#include <time.h>
#include "Cell.h"

int initBoard(sudoCell ptr[9][9]);
int copyBoard(sudoCell solution[9][9], sudoCell puzzle[9][9]);
int checkNum(sudoCell board[9][9], int number, int row, int col);
int allOptions(int allNums[9],sudoCell board[9][9], int row, int col);
int updateList(int allNums[9], int actualSize, int index);
int backtracking(sudoCell board[9][9], int row, int col, int mode);
int updatePuzzle(sudoCell solution[9][9], sudoCell puzzle[9][9], int mode);

#endif
