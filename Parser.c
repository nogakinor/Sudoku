#include "Parser.h"
#include "Game.h"
#include "Cell.h"

/*
    sets the board with given number of fixed cells (given by the user).
    changes the variable progress which represents the number of full cells on the board
*/
int startGame(sudoCell board[9][9], sudoCell playerBoard[9][9], int* progress){
    int cellNum = -1, randRow, randCell, cellCount = 0;
    printf("Please enter the number of cells to fill [0-80]:\n");
    if(scanf("%d", &cellNum)!= 1){
        if (cellNum != EOF || !feof(stdin) || cellNum != -1 ){
            printf("Error: not a number\n");
        }
        return 0;
    }
    getchar();
    while(cellNum > 9*9 - 1 || cellNum < 0){
        if (cellNum == EOF || feof(stdin) ){
            return 0;
        }
        printf("Error: invalid number of cells to fill (should be between 0 and 80)\n");
        printf("Please enter the number of cells to fill [0-80]:\n");
        if(scanf("%d", &cellNum)!=1){
            if (cellNum != EOF || !feof(stdin)  ){
                printf("Error: not a number\n");
            }
            return 0;
        }
        getchar();
    }
    *progress = cellNum;
    while(cellCount < cellNum){
        randRow = rand() % 9;
        randCell = rand() % 9;
        if (board[randCell][randRow].isFixed != '.') {
            playerBoard[randCell][randRow].value = board[randCell][randRow].value;
            playerBoard[randCell][randRow].isFixed = '.';
            board[randCell][randRow].isFixed = '.';
            cellCount++;
        }
    }
    return 1;
}


int convert(char num){
  return num - '0';
}

/*
    parse user's command into its arguments
    if set - receives 3 arguments, if hint - receives 2 arguments
    if not enough arguments were given will return 0 (invalid command)
*/
int parse(char* str, int ans[3], int i){
    int j;
    ans[2] = 0;
    for(j=0; j<3;j++){
        if (j == 2 && i == 3){
            if(ans[0]<=0 || ans[1] >9 || ans[0] >9 || ans[1]<=0){
                return 0;
            }
            return i;
        }
        str = strtok(NULL, " \t\r\n");
        if (str == NULL){
            return 0;
        }
        ans[j] = convert(str[0]);

    }
    if(ans[2]<0 || ans[2] >9) {
        return 0;
    }
  return i;

}


/*
    function gets a command from user and returns a number representing the command.
    gets as argument an array of integers representing the command's arguments
*/
int userInput(int cells[3]){
  char str[1024], *token;
  do {
      if(!fgets(str, 1024, stdin)|| ferror(stdin)) {
          return 4;
      }
      token = strtok(str, " \t\r\n");
  }
  while(token == NULL && !feof(stdin));
  if(strncmp(token, "validate", 8) == 0){
    return 1;
  }

  else if (strncmp(token, "restart", 7) == 0){
    return 2;
  }

  else if(strncmp(token, "hint", 4) == 0){

    return  parse(token, cells, 3);
  }

  else if(strncmp(token, "exit", 4) == 0){
    return 4;
  }

  else if(strncmp(token, "set", 3) == 0){

    return parse(token, cells, 5);
  }
  return 0;
}