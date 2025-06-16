#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

/*
 * allocateMaze:
 *   - Allocate an array of 'rows' pointers (char*), then allocate each row of length 'cols'.
 *   - Return the char** so that *(*(maze + r) + c) is valid.
 */
char ** allocateMaze(int rows, int cols) {
    int r;
    char **maze = (char **)malloc(rows * sizeof(char *));
    if (!maze) {
        fprintf(stderr, "Failed to allocate row pointers.\n");
        return NULL;
    }

    for (r = 0; r < rows; ++r) {
        /* *(maze + r) is the same as maze[r], but uses pointer arithmetic */
        *(maze + r) = malloc(cols * sizeof(char));
        if (!*(maze + r)) {
            perror("malloc");
            /* free any rows we already got */
            while (r-- > 0) free(*(maze + r));
            free(maze);
            return NULL;
        }
    }
    return maze;
}

/*
 * fillWithWalls:
 *   - Set every cell in a rows×cols array to '#'.
 *   - Use pointer arithmetic: *(*(maze + r) + c) = '#';
 */
void fillWithWalls(char **maze, int rows, int cols) {
    int r, c;
    for (r = 0; r < rows; r++) {
        for (c = 0; c < cols; c++) {
            *(*(maze + r) + c) = '#';
        }
    }
}

/*
 * printMaze:
 *   - Loop over rows and cols, printing each character.
 *   - After each row, print '\n'.
 *   - Use only pointer arithmetic to access cells.
 */
void printMaze(char **maze, int rows, int cols) {
    int r, c;
    for (r = 0; r < rows; r++) {
        for (c = 0; c < cols; c++) {
            putchar(*(*(maze + r) + c));
        }
        putchar('\n');
    }
}

/*
 * freeMaze:
 *   - Free each row, then free the array of row pointers.
 */
void freeMaze(char **maze, int rows) {
    int r;
    if (!maze) return;
    for (r = 0; r < rows; ++r) {
        free(*(maze + r));
    }
    free(maze);
}
