#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Game.h"
#include "Parser.h"
#include "Solver.h"
#include "Cell.h"

int main(int argc, char *argv[]) {

    unsigned int seed;
    if (argc < 1) {
        return 1;
    }
    seed = atoi(argv[1]);
    srand(seed);
    init();
    return 0;
}