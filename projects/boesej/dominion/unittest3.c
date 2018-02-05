/***************************************************
 *File name: unittest3.c
 *Author: Jonathan Boese
 *Date: 2/28/2018
 *Description: Testing the function scoreFor from dominion.c using the
 * fullDeckCount which has been verified to run correctly.
****************************************************/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define MAX_TESTS 5

int main() {

    struct gameState* game;
    int randomPlayer;
    int totalScore;
    int functionScore;
    int totalDeckSize;
    int numbPlayers = 0;
    int errors = 0;
    int i,j,k,l;
    srand(time(0));

    for (i = 0; i < MAX_TESTS; ++i) {
        
        game = malloc(sizeof(struct gameState));

        totalScore = 0;
        functionScore = 0;
        totalDeckSize = 0;

        randomNewGame(game);

        numbPlayers = game->numPlayers;

        randomPlayer = rand() % (numbPlayers + 1 - 2) + 2;

        randomizeGameState(game);

        totalScore -= fullDeckCount(randomPlayer, 0, game);     // Curse score

        totalScore += fullDeckCount(randomPlayer, 1, game);     // Score for Estate cards

        totalScore += (fullDeckCount(randomPlayer, 2, game) * 3);     // Score for Duchy cards

        totalScore += (fullDeckCount(randomPlayer, 3, game) * 6);     // Score for Province cards

        totalScore += fullDeckCount(randomPlayer, 16, game);    // Score for Great Hall cards

        totalDeckSize = (game->deckCount[randomPlayer] +
                game->handCount[randomPlayer] +
                game->discardCount[randomPlayer]);

        totalScore += (totalDeckSize / 10);        // Score for Gardens cards - sum all cards and divide by 10

        functionScore = scoreFor(randomPlayer, game);

        if(totalScore != functionScore){

            errors++;
            printf("Error! Test #%i:\nCorrect total score: %i, functions calculated score: %i\n\n",
                   i+1, totalScore, functionScore);
            printf("Total curse cards: %i\n",fullDeckCount(randomPlayer,0,game));
            printf("Total estate cards: %i\n",fullDeckCount(randomPlayer,1,game));
            printf("Total Duchy cards: %i\n",fullDeckCount(randomPlayer,2,game));
            printf("Total Province cards: %i\n",fullDeckCount(randomPlayer,3,game));
            printf("Total Great Hall cards: %i\n",fullDeckCount(randomPlayer,16,game));
            printf("Total number of cards in deck: %i\nTotal score for Gardens: %i\n\n", totalDeckSize, (totalDeckSize / 10));
        }

        free(game);
    }

    printf("Detected %i errors\n\n", errors);
    return 0;
}