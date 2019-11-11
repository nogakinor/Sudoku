

#ifndef UNTITLED_PARSER_H
#define UNTITLED_PARSER_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Cell.h"

int startGame(sudoCell board[9][9], sudoCell playerBoard[9][9], int* progress);
int convert(char num);
int parse(char* str, int ans[3], int i);
int userInput(int cells[3]);


#endif
