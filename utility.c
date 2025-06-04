#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

/*
 * allocateMaze:
 *   - Allocate an array of 'rows' pointers (char*), then allocate each row of length 'cols'.
 *   - Return the char** so that *(*(maze + r) + c) is valid.
 */
char ** allocateMaze(int rows, int cols) {
    int i;
    char **maze = (char **)malloc(rows * sizeof(char *));
    if (!maze) {
        fprintf(stderr, "Failed to allocate row pointers.\n");
        return NULL;
    }

    for (i = 0; i < rows; i++) {
        maze[i] = (char *)malloc(cols * sizeof(char));
        if (!maze[i]) {
            fprintf(stderr, "Failed to allocate row %d.\n", i);
            while (i-- > 0) {
                free(maze[i]);
            }
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
    int i;
    if (!maze) return;
    for (i = 0; i < rows; i++) {
        free(maze[i]);
    }
    free(maze);
}
