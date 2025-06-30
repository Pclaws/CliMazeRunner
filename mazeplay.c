#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "mazeplay.h"
#include "utility.h"

/*
 * findPlayer:
 *   - Scan the entire maze to locate 'S'. Return 1 if found (and set *r, *c), or 0 if not found.
 *   - Uses pointer arithmetic only.
 */
static int findPlayer(char **maze, int rows, int cols, int *r, int *c) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (*(*(maze + i) + j) == 'S') {
                *r = i;
                *c = j;
                return 1;
            }
        }
    }
    return 0;
}

/**
 * playMaze:
 *   - Lets the player move through the maze using W/A/S/D keys.
 *   - Tracks the number of valid steps (not counting walls).
 *   - Returns number of moves if the player reaches the exit ('E').
 *   - Returns 0 if the player quits by pressing 'Q'.
 */
int playMaze(char **maze, int rows, int cols) {
    int pr, pc;           /** player's current row and column */
    int dr = 0, dc = 0;   /** change in row/col based on movement */
    int moves = 0;        /** counts successful moves */
    char input;           /** stores the user's input */

    /** Find the starting position 'S' in the maze */
    if (!findPlayer(maze, rows, cols, &pr, &pc)) {
        return 0; /** Should never happen, but return 0 just in case */
    }

    while (1) {
        /** Show the current maze */
        printMaze(maze, rows, cols);
        printf("\nMove (W/A/S/D) or Q to quit: ");

        /** Read user input (ignore newlines) */
        do {
            input = getchar();
        } while (input == '\n');

        /** Flush the rest of the line */
        while (getchar() != '\n');

        /** Convert input to uppercase to handle both lowercase and uppercase */
        input = toupper((unsigned char)input);

        /** Check for quit command */
        if (input == 'Q') {
            return 0; /** Player quit early */
        }

        /** Reset movement deltas */
        dr = dc = 0;

        /** Determine direction based on input */
        if (input == 'W') {
            dr = -1;
        } else if (input == 'S') {
            dr = 1;
        } else if (input == 'A') {
            dc = -1;
        } else if (input == 'D') {
            dc = 1;
        } else {
            continue; /** Ignore invalid keys */
        }

        /** Calculate target cell based on move */
        {
            int tr = pr + dr;
            int tc = pc + dc;

            /** Check if the target is outside the maze */
            if (tr < 0 || tr >= rows || tc < 0 || tc >= cols) {
                printf("\nYou walked into a wall!\n\n");
                continue;
            }

            char target = *(*(maze + tr) + tc);

            /** If it's a wall, don't move */
            if (target == '#') {
                printf("\nYou walked into a wall!\n\n");
                continue;
            }

            /** It's a valid move: count it */
            moves++;

            /** Check if the player reached the exit */
            if (target == 'E') {
                *(*(maze + pr) + pc) = '*';       /** Mark previous spot */
                *(*(maze + tr) + tc) = 'S';       /** Move player */
                printMaze(maze, rows, cols);
                printf("\nCongratulations! You reached the exit in %d moves.\n\n", moves);
                return moves; /** return number of moves as score */
            }

            /** Regular move (onto '.' or '*'): update position */
            *(*(maze + pr) + pc) = '*';   /** mark old position */
            *(*(maze + tr) + tc) = 'S';   /** place 'S' at new position */
            pr = tr;  /** update current row */
            pc = tc;  /** update current column */
            printf("\n");
        }
    }
}