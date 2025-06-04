#ifndef MAZEGEN_H
#define MAZEGEN_H

/*
 * generateMaze:
 *   - Carve out a random-walk path from a start on row 0 to an exit on row rows-1.
 *   - Ensure that no more than 1/4 of all cells become open; if they do, restart.
 *   - Place 'S' on row 0 (not in corners) and 'E' on row rows-1 (where the walk ends).
 *   - Arguments:
 *       maze : a rows×cols grid (all '#' initially)
 *       rows : total number of rows (10–20)
 *       cols : total number of columns (10–20)
 */
void generateMaze(char **maze, int rows, int cols);

#endif /* MAZEGEN_H */
