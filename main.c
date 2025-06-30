#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "utility.h"
#include "mazegen.h"
#include "mazeplay.h"

#define MAX_NAME_LEN 100
#define MAX_BEST_SCORES 3

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
    int rows, cols;
    char **maze = NULL;
    char again;
    int bestScores[MAX_BEST_SCORES] = {0};
    int i;
    int winMoves;

    char *playerName = NULL;
    char nameInput[MAX_NAME_LEN];

    srand((unsigned)time(NULL));

    printf("Welcome to Maze Runner!\n\n");
    printf("Enter your name: ");
    fgets(nameInput, MAX_NAME_LEN, stdin);
    nameInput[strcspn(nameInput, "\n")] = '\0';

    playerName = malloc(strlen(nameInput) + 1);
    if (!playerName) {
        fprintf(stderr, "Memory allocation for name failed.\n");
        return EXIT_FAILURE;
    }
    strcpy(playerName, nameInput);

    do {
        rows = 10 + (rand() % 11);
        cols = 10 + (rand() % 11);

        maze = allocateMaze(rows, cols);
        if (!maze) {
            fprintf(stderr, "Memory allocation failed. Exiting.\n");
            free(playerName);
            return EXIT_FAILURE;
        }

        generateMaze(maze, rows, cols);

        winMoves = playMaze(maze, rows, cols);
        if (winMoves > 0) {
            printf("Well done, %s!\n", playerName);
            updateBestScores(bestScores, winMoves);
        } else {
            printf("Sorry you did not make it out.\n");
        }

        freeMaze(maze, rows);
        maze = NULL;

        printf("Would you like to play again? (Y/N): ");
        do {
            again = getchar();
        } while (again == '\n');
        while (getchar() != '\n');
        again = toupper((unsigned char)again);
        printf("\n");

    } while (again == 'Y');

    printf("Thanks for playing, %s!\n", playerName);
    printf("Your Top %d Scores:\n", MAX_BEST_SCORES);
    for (i = 0; i < MAX_BEST_SCORES; i++) {
        if (bestScores[i] > 0) {
            printf("%d) %d moves\n", i + 1, bestScores[i]);
        }
    }

    free(playerName);
    printf("...Exiting game by Letshu Phinees Abel\n");
    return EXIT_SUCCESS;
}
