/***************************************************
 *File name: unittest1.c
 *Author: Jonathan Boese
 *Date: 2/28/2018
 *Description: Testing the function fullDeckCount from dominion.c
****************************************************/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define MAX_TESTS 1000

int main(){

    struct gameState* game;
    int numInDeck = 0;
    int randomNumber = 0;
    int calculatedDeckNum = 0;
    int i;
    int j;
    int numPlayers = 0;
    srand((time(0)));

    for (i = 0; i < MAX_TESTS; ++i) {

        game = malloc(sizeof(struct gameState));

        calculatedDeckNum = 0;

        randomNewGame(game);

        numPlayers = game->numPlayers;

        randomNumber = rand() % (26 + 1 - 0);

        while (game->supplyCount[randomNumber] < 1) {

            randomNumber = rand() % (26 + 1 - 0);
        }

        numInDeck = game->supplyCount[randomNumber];

        randomizeGameState(game);

        for (j = 0; j < numPlayers; ++j) {

            calculatedDeckNum += fullDeckCount(j, randomNumber, game);
        }

        if (numInDeck != (calculatedDeckNum + game->supplyCount[randomNumber])) {

            printf("Error found in test #%i:\nNumber of players: %i\nCard(as int): %i\nTotal Supply: %i\nTotal as found by function: %i\n",
                   i, numPlayers, randomNumber, numInDeck, calculatedDeckNum);
            free(game);
            return 1;
        }

        free(game);
    }

    printf("%i tests completed, no errors detected in fullDeckCount.\n\n", MAX_TESTS);
    return 0;
}
