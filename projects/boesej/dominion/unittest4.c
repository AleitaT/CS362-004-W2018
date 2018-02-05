/***************************************************
 *File name: unittest4.c
 *Author: Jonathan Boese
 *Date: 2/28/2018
 *Description: Testing the function supplyCount function from dominion.c
****************************************************/


#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define MAX_TESTS 1000


int main(){

    struct gameState* game;
    int numPlayers =0;
    int randomCard;
    int supplyLeft;
    int totalTaken;
    int functionTotal;
    int errors = 0;
    int i,j,k,l;

    for (i = 0; i < MAX_TESTS; ++i) {

        game = malloc(sizeof(struct gameState));
        totalTaken = 0;

        randomNewGame(game);

        numPlayers = game->numPlayers;

        randomCard = rand() % (26 + 1 - 0);

        supplyLeft = game->supplyCount[randomCard];

        randomizeGameState(game);

        for (j = 0; j < numPlayers; ++j) {

            totalTaken += fullDeckCount(j, randomCard, game);
        }

        supplyLeft -= totalTaken;

        functionTotal = supplyCount(randomCard, game);

        if(supplyLeft != functionTotal){

            errors++;
            printf("Correct supply remaining: %i, function total: %i\n\n");
        }

        free(game);
    }

    printf("Detected %i errors in %i tests!\n\n", errors, MAX_TESTS);
    return 0;
}