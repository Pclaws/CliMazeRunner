#include <stdio.h>
#include <ctype.h>
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

/*
 * playMaze:
 *   - Handle the user’s W/A/S/D/Q input until either 'E' is reached or Q is pressed.
 *   - Return 1 if the user won, 0 if they quit.
 */
int playMaze(char **maze, int rows, int cols) {
    int pr, pc;           /* player row, col */
    int dr = 0, dc = 0;   /* delta row/col for the move */
    int moves = 0;
    char input;

    /* Locate initial 'S' */
    if (!findPlayer(maze, rows, cols, &pr, &pc)) {
        return 0; /* no player found—shouldn't happen */
    }

    while (1) {
        /* 1) Print the current maze */
        printMaze(maze, rows, cols);
        printf("\nMove (W/A/S/D) or Q to quit: ");

        /* 2) Read one non‐newline char from stdin */
        do {
            input = getchar();
        } while (input == '\n');
        /* Discard remaining until end of line */
        while (getchar() != '\n');

        input = toupper((unsigned char)input);

        if (input == 'Q') {
            return 0; /* quit early */
        }

        /* 3) Determine dr,dc based on input */
        dr = dc = 0;
        if (input == 'W') {
            dr = -1;
        } else if (input == 'S') {
            dr = 1;
        } else if (input == 'A') {
            dc = -1;
        } else if (input == 'D') {
            dc = 1;
        } else {
            /* Invalid key: ignore and re‐loop */
            continue;
        }

        /* 4) Compute target cell */
        {
            int tr = pr + dr;
            int tc = pc + dc;

            /* Check bounds */
            if (tr < 0 || tr >= rows || tc < 0 || tc >= cols) {
                /* Outside maze—treat as wall */
                printf("\nYou walked into a wall!\n\n");
                continue;
            }

            char target = *(*(maze + tr) + tc);

            if (target == '#') {
                /* Hit a wall */
                printf("\nYou walked into a wall!\n\n");
                continue;
            }
            /* Otherwise, target is either '.', '*' (visited), or 'E'. */

            /* 5) Valid move: increment moves */
            moves++;

            /* 6) Check if stepping into 'E' */
            if (target == 'E') {
                /* Mark previous position as '*' */
                *(*(maze + pr) + pc) = '*';
                /* Move player onto E (we'll overwrite E with S for display) */
                *(*(maze + tr) + tc) = 'S';
                printMaze(maze, rows, cols);
                printf("\nCongratulations! You reached the exit in %d moves.\n\n", moves);
                return 1;
            }

            /* 7) Regular corridor ('.' or '*'): mark previous as '*' */
            *(*(maze + pr) + pc) = '*';
            /* Move player (place 'S' at new position) */
            *(*(maze + tr) + tc) = 'S';
            pr = tr;
            pc = tc;
            printf("\n");
        }
    }
}
