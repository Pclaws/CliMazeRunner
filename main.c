#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "utility.h"
#include "mazegen.h"
#include "mazeplay.h"

int main(void) {
    int rows, cols;
    char **maze = NULL;
    char again;

    /* Seed the RNG once */
    srand((unsigned)time(NULL));

    printf("Welcome to Maze Runner!\n\n");

    do {
        /* 1) Pick random dimensions between 10 and 20 */
        rows = 10 + (rand() % 11);
        cols = 10 + (rand() % 11);
        printf("DEBUG: rows=%d, cols=%d\n\n", rows, cols);

        /* 2) Allocate a rows×cols maze */
        maze = allocateMaze(rows, cols);
        if (!maze) {
            fprintf(stderr, "Memory allocation failed. Exiting.\n");
            return EXIT_FAILURE;
        }

        /* 3) Generate a maze with at least one path S→E */
        generateMaze(maze, rows, cols);

        /* 4) Let the user play until they win or quit early */
        if (!playMaze(maze, rows, cols)) {
            /* Player quit early */
            printf("Sorry you did not make it out.\n\n");
        }

        /* 5) Free the maze before playing again */
        freeMaze(maze, rows);
        maze = NULL;

        /* 6) Prompt to play again */
        printf("Would you like to play again? (Y/N): ");
        do {
            again = getchar();
        } while (again == '\n');
        while (getchar() != '\n'); /* flush rest of line */
        again = toupper((unsigned char)again);
        printf("\n");

    } while (again == 'Y');

    printf("Thanks for playing Maze Runner by Letshu Phinees Abel!\n");
    return EXIT_SUCCESS;
}
