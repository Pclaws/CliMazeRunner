#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "utility.h"
#include "mazegen.h"
#include "mazeplay.h"

#define MAX_NAME_LEN 100      /** Maximum length for player name */
#define MAX_BEST_SCORES 3     /** Track top 3 scores */

/** 
 * updateBestScores:
 *   - Maintains the top 3 lowest move counts (best scores).
 *   - Inserts newScore into the correct position if it qualifies.
 */
void updateBestScores(int *bestScores, int newScore) {
    int i, j;
    for (i = 0; i < MAX_BEST_SCORES; i++) {
        if (bestScores[i] == 0 || newScore < bestScores[i]) {
            for (j = MAX_BEST_SCORES - 1; j > i; j--) {
                bestScores[j] = bestScores[j - 1];
            }
            bestScores[i] = newScore;
            break;
        }
    }
}

int main(void) {
    int rows, cols;                  /** Maze dimensions */
    char **maze = NULL;             /** Maze represented as char** */
    char again;                     /** Replay input */
    int bestScores[MAX_BEST_SCORES] = {0};  /** Array to hold top 3 scores */
    int i;                          /** Loop counter */
    int winMoves;                   /** Moves taken in current game */

    char *playerName = NULL;        /** Dynamically allocated player name */
    char nameInput[MAX_NAME_LEN];   /** Temporary buffer for input */

    srand((unsigned)time(NULL));    /** Seed random number generator */

    printf("Welcome to Maze Runner!\n\n");

    /** Prompt for player's name */
    printf("Enter your name: ");
    fgets(nameInput, MAX_NAME_LEN, stdin);
    nameInput[strcspn(nameInput, "\n")] = '\0';  /** Remove newline */

    /** Allocate memory just enough for player name */
    playerName = malloc(strlen(nameInput) + 1);
    if (!playerName) {
        fprintf(stderr, "Memory allocation for name failed.\n");
        return EXIT_FAILURE;
    }
    strcpy(playerName, nameInput);

    /** Game loop: repeat until player chooses not to play */
    do {
        rows = 10 + (rand() % 11);  /** Random height between 10–20 */
        cols = 10 + (rand() % 11);  /** Random width between 10–20 */

        maze = allocateMaze(rows, cols);
        if (!maze) {
            fprintf(stderr, "Memory allocation failed. Exiting.\n");
            free(playerName);
            return EXIT_FAILURE;
        }

        generateMaze(maze, rows, cols); /** Create new maze with guaranteed path */

        winMoves = playMaze(maze, rows, cols); /** Play and get move count if win */

        if (winMoves > 0) {
            printf("Well done, %s!\n", playerName);
            updateBestScores(bestScores, winMoves); /** Update top scores */
        } else {
            printf("Sorry you did not make it out.\n");
        }

        freeMaze(maze, rows);  /** Free memory used by maze */
        maze = NULL;

        /** Ask if player wants to play again */
        printf("Would you like to play again? (Y/N): ");
        do {
            again = getchar();
        } while (again == '\n');
        while (getchar() != '\n');
        again = toupper((unsigned char)again);
        printf("\n");

    } while (again == 'Y');

    /** Display final top scores */
    printf("Thanks for playing, %s!\n", playerName);
    printf("Your Top %d Scores:\n", MAX_BEST_SCORES);
    for (i = 0; i < MAX_BEST_SCORES; i++) {
        if (bestScores[i] > 0) {
            printf("%d) %d moves\n", i + 1, bestScores[i]);
        }
    }

    free(playerName);  /** Free memory used by name */
    printf("...Exiting game by Letshu Phinees Abel\n");
    return EXIT_SUCCESS;
}
