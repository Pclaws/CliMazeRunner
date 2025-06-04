#ifndef MAZEPLAY_H
#define MAZEPLAY_H

/*
 * playMaze:
 *   - Let the user move with W/A/S/D (case‐insensitive) and Q to quit.
 *   - Start with 'S' marking the player on row 0. On each valid move:
 *       • If move hits '#', print “You walked into a wall!” and do not increment move count.
 *       • If move steps into '.', increment move count, mark the previous cell with '*', 
 *         and draw 'S' at the new location.
 *       • If move steps into 'E', increment move count and return 1 (win).
 *       • After every key press (including invalid/wall‐hits), re‐print the maze.
 *   - Count only successful moves (not wall‐hits).
 *   - Return 1 if the player reached 'E', or 0 if the player pressed Q (quit early).
 */
int playMaze(char **maze, int rows, int cols);

#endif /* MAZEPLAY_H */
