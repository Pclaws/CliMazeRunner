#ifndef UTILITY_H
#define UTILITY_H

/* 
 * Allocate a rows×cols maze (char**). Return NULL on failure.
 */
char ** allocateMaze(int rows, int cols);

/* Fill every cell of the maze with walls ('#') */
void fillWithWalls(char **maze, int rows, int cols);

/* Print the maze to stdout, using pointer arithmetic only */
void printMaze(char **maze, int rows, int cols);

/* Free all memory allocated for a rows×cols maze */
void freeMaze(char **maze, int rows);

#endif /* UTILITY_H */
