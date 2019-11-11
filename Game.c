#include <stdio.h>
#include "Game.h"

/*
prints a given board of Cells
*/
int printBoard(sudoCell board[9][9]){
    int i, j, minusi = 0, minusj = 0;
    for (i = 0; i < 13; i++){
        if(i==0 || i == 4 || i == 8 || i == 12){
            printf("----------------------------------\n");
            minusi++;
        }
        else{
            for(j = 0; j < 13; j++) {
                if(j==0 || j == 4 || j == 8 || j == 12) {
                    printf("|");
                    if(j != 12){
                        printf(" ");
                    }
                    minusj++;
                    continue;
                }
                else if (board[i - minusi][j - minusj].value != 0){
                    printf("%c%d", board[i - minusi][j - minusj].isFixed ,board[i - minusi][j - minusj].value);
                }
                else {
                    printf("  ");
                }
                printf(" ");
            }
            printf("\n");
            minusj = 0;
        }
    }
    return 0;
}

/*
    sets playBoard[row][col] = num
*/
int setCell(sudoCell playerBoard[9][9], int col, int row, int num, int* progress){
    row--;
    col--;
    if (playerBoard[row][col].isFixed == '.'){
        printf("Error: cell is fixed\n");
        return 0;
    }
    if (num == 0 || checkNum(playerBoard, num, row, col)){
        if(num == 0){
            --*progress;
        }
        else{
            ++*progress;
        }
        playerBoard[row][col].value = num;
        printBoard(playerBoard);
        return 1;
    }
    printf("Error: value is invalid\n");
    return 0;
}

/*
    operates the game according to user's commands
    runs as long as long as the user hasn't entered restart or exit
    if command is invalid will print accordingly
    1 = validate, 2 = restart, 3 = hint, 4 = exit, 5 = set
    done - is the bored solved. changes to 1 if progress is 81
*/
int begin(sudoCell ptr[9][9], sudoCell playerBoard[9][9], int* progress){
    int inputCells[3], command, done = 0;
    printBoard(playerBoard);
    while(1){
        command = userInput(inputCells);
        if(!command){
            printf("Error: invalid command\n");
        }
        else {
            switch (command) {
                case 1: {
                    if (!done) {
                        if (!updatePuzzle(ptr, playerBoard, 1)) {
                            printf("Validation failed: board is unsolvable\n");
                        }
                        else {
                            printf("Validation passed: board is solvable\n");
                        }
                    }
                    break;
                }
                case 2: {

                    return 0;
                }
                case 3: {
                    if (!done) {
                        printf("Hint: set cell to %d\n", ptr[inputCells[1] - 1][inputCells[0] - 1].value);
                    }
                    break;
                }
                case 4: {
                    printf("Exiting...\n");
                    return 1;
                }
                case 5: {
                    if (!done) {
                        setCell(playerBoard, inputCells[0], inputCells[1], inputCells[2], progress);
                    }
                    break;
                }
                default: {
                    printBoard(playerBoard);
                    printf("\n");
                }
            }
            if (done) {
                printf("Error: invalid command\n");
            }
            if (*progress >= 81 && !done) {
                printf("Puzzle solved successfully\n");
                done = 1;
            }
        }

    }
}


/*
    setting the game board and solution board
    runs as long as the player hasn't entered exit
*/
int init() {
    sudoCell ptr[9][9];
    sudoCell playerBoard[9][9];
    int progress = 0;
    initBoard(playerBoard);
    updatePuzzle(ptr, playerBoard, 0);
    if(!startGame(ptr, playerBoard, &progress)){
        printf("Exiting...\n");
        return 0;
    }

    while(!begin(ptr, playerBoard, &progress)){
        initBoard(playerBoard);
        updatePuzzle(ptr, playerBoard, 0);
        progress = 0;
        if(!startGame(ptr, playerBoard, &progress)){
            printf("Exiting...\n");
            return 0;
        }
    }
    return 0;
}
