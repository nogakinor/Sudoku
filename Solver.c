#include "Solver.h"

/*
    creates empty board of cells
*/
int initBoard(sudoCell ptr[9][9]){
    int i, j;
    for(i = 0; i< 9; i++){
        for(j = 0; j < 9; j++){
            ptr[i][j].value = 0;
            ptr[i][j].isFixed = ' ';
        }
    }
    return 0;
}

/*
    copies board puzzle into board solution, and fixes all cells that are not 0. used to check validation.
*/
int copyBoard(sudoCell solution[9][9], sudoCell puzzle[9][9]){
    int i, j;
    for(i = 0; i< 9; i++){
        for(j = 0; j < 9; j++){
            solution[i][j].value = puzzle[i][j].value;
            solution[i][j].isFixed = ' ';
            if(puzzle[i][j].value != 0){
                solution[i][j].isFixed = '.';
            }
        }
    }
    return 0;
}

/*
    checks if number is a valid value for board[row][col]
*/
int checkNum(sudoCell board[9][9], int number, int row, int col){
    /*
     * blockRow and blockCol for block check
     */
    int i, j, k, blockRow = (row - (row%3)), blockCol = (col - (col%3));
    for (i = 0; i < 9; i++){
        if (board[i][col].value == number || board[row][i].value == number){
            return 0;
        }
    }
    for(j = 0; j < 3; j++) {
        for(k = 0; k < 3; k++){
            if (board[blockRow + k][blockCol + j].value == number) {
                return 0;
            }
        }
    }
    return 1;
}

/*
    sets allNums[] with all valid values for board[row][col].
    returns the actual size of allNums (number of valid values)
*/
int allOptions(int allNums[9],sudoCell board[9][9], int row, int col){
    int i, place = 0;
    for(i = 1; i < 10; i++) {
        if (checkNum(board, i, row, col)){
            allNums[place] = i;
            place++;
        }
    }
    return place;
}

/*
    replaces between last element and the element we just used. return new size.
    used to update elements list in the random backtracking algorithm.
*/
int updateList(int allNums[9], int actualSize, int index){
    int i;
    for (i = index + 1; i < actualSize; i++){
        allNums[i - 1] = allNums[i];
    }
    return actualSize - 1;
}

int backtracking(sudoCell board[9][9], int row, int col, int mode) {
    int i, j, valid, value, place;
    int allNums[9]= {0};
    if (col == 9 && row == 8) {
        return 1;
    }
    if (col == 9 && row < 8) {
        col = 0;
        row++;
    }
    if (board[row][col].isFixed == '.') {
        return backtracking(board, row, col + 1, mode);
    }
    /*
     * mode = 1 if deterministic
     */
    if(mode == 1){
        for(i = 1; i<10; i++){
            valid= checkNum(board, i, row, col);
            if(valid){
                board[row][col].value = i;
                if(backtracking(board, row, col + 1, mode)) {
                    return 1;
                }
                board[row][col].value = 0;
            }
        }


    }
    /*
     * else, mode is random
     */
    else {
        j = allOptions(allNums, board, row, col);
        while(j>0) {
            if(j==1) {
                value = allNums[--j];
                }
            else{
                place = rand() % j;
                value = allNums[place];
                j = updateList(allNums, j, place);
                }

            board[row][col].value = value;

            if(backtracking(board, row, col + 1, mode)) {
                return 1;
                }
            board[row][col].value = 0;
            }
        }
    return 0;
}

/*
    will check if puzzle is solvable. if so will keep the solution in solution.
    else will return last solution and print the board is not solvable.
*/
int updatePuzzle(sudoCell solution[9][9], sudoCell puzzle[9][9], int mode){
    int num;
    sudoCell keepBoard[9][9];
    copyBoard(keepBoard, solution);
    copyBoard(solution, puzzle);
    num = backtracking(solution, 0, 0, mode);
    if(!num){
        copyBoard(solution, keepBoard);
    }
    return num;
}
