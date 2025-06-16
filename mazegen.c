#include <stdlib.h>
#include <time.h>
#include "mazegen.h"
#include "utility.h"

/*
 * carvePathUntilExit:
 *   - Starting from (0, startCol) where 'S' sits, perform a random walk
 *     that carves out (turns '#' → '.') until reaching row (rows-1).
 *   - Every time the walk enters a '#' cell, turn it into '.'. The final cell
 *     on row (rows-1) is then replaced by 'E'.
 *   - Because we only exit once we reach row (rows-1), there is always a path
 *     of '.' from S to E.
 */
static void carvePathUntilExit(char **maze, int rows, int cols, int startCol) {
    int curRow = 0, curCol = startCol;
    int dir, newRow, newCol;

    /* Ensure the cell under 'S' is open when we step into it: */
    if (rows > 1) {
        /* Carve the cell directly below the start so we can begin walking */
        *(*(maze + 1) + startCol) = '.';
        curRow = 1;
        curCol = startCol;
    }

    /* always carve exactly one cell into the interior */
    *(*(maze + 1) + startCol) = '.';
    curRow = 1;
    curCol = startCol;

    /* Walk until we reach the bottom row (rows-1) */
    while (curRow < rows - 1) {
        dir = rand() % 4; /* 0=up,1=down,2=left,3=right */
        newRow = curRow;
        newCol = curCol;

        if (dir == 0) {
            newRow = curRow - 1;
        } else if (dir == 1) {
            newRow = curRow + 1;
        } else if (dir == 2) {
            newCol = curCol - 1;
        } else {
            newCol = curCol + 1;
        }

        /* Check bounds; ignore moves that would leave the grid */

        /* Only carve inside the inner (rows−2×cols−2) area */
        if (newRow < 1 || newRow > rows - 2|| newCol < 1 || newCol > cols - 2) {
             continue;
        }

        /* Carve if we're on a wall */
        if (*(*(maze + newRow) + newCol) == '#') {
            *(*(maze + newRow) + newCol) = '.';
        }

        /* Move the “walker” */
        curRow = newRow;
        curCol = newCol;

        /* Optionally stop early if you’ve hit the last interior row */
        if (curRow == rows - 2)
            break;

    }

    /* Now curRow == rows-1; place 'E' there (overwriting the '.') */
    /* Place the exit just below at the bottom border—which is the only carve allowed there */
    *(*(maze + (rows - 1)) + curCol) = 'E';
}

/*
 * countOpenSpaces:
 *   - Return the number of cells that are not '#' (i.e. '.' or 'S' or 'E' or '*').
 *   - Used to enforce the “no more than 1/4 open” rule.
 */
static int countOpenSpaces(char **maze, int rows, int cols) {
    int r, c, cnt = 0;
    for (r = 0; r < rows; r++) {
        for (c = 0; c < cols; c++) {
            char ch = *(*(maze + r) + c);
            if (ch != '#') {
                cnt++;
            }
        }
    }
    return cnt;
}

/*
 * generateMaze:
 *   - Loop until we generate a maze with ≤ (rows*cols)/4 open cells.
 *   - Each attempt:
 *       1) Fill all walls ('#').
 *       2) Pick a random startCol in [1..cols-2], place 'S' at (0,startCol).
 *       3) Carve a path via carvePathUntilExit().
 *       4) Count open spaces; if > 1/4, repeat from step 1.
 *   - By construction, there is always a '.'‐chain from S → E.
 */
void generateMaze(char **maze, int rows, int cols) {
    int startCol, openCount, maxOpen = (rows * cols) / 4;

    do {
        /* 1) fill with walls */
        fillWithWalls(maze, rows, cols);

        /* 2) choose S on top row (not corners) */
        startCol = 1 + (rand() % (cols - 2));
        *(*(maze + 0) + startCol) = 'S';

        /* 3) carve path until bottom row, placing 'E' appropriately */
        carvePathUntilExit(maze, rows, cols, startCol);

        /* 4) count open spaces (any char ≠ '#'): if too many, retry */
        openCount = countOpenSpaces(maze, rows, cols);
    } while (openCount > maxOpen);
}
