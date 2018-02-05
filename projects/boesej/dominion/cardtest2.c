/***************************************************
 *File name: cardtest2.c
 *Author: Jonathan Boese
 *Date: 2/28/2018
 *Description: Testing the refactoredAdventurer function from dominion.c
****************************************************/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define MAX_TESTS 1000


int main(){

    struct gameState* game;
    int i,j,k,l;
    int numPlayers;
    int totalTreasures = 0;
    int drawnTreasures = 0;
    int totalDeckSize;
    int discardErrors = 0;
    int drawErrors = 0;
    int totalHandSize = 0;
    int totalDiscardSize;
    int treasureError = 0;
    int totalErrors;
    int playerWithCard;
    int failedToDiscardAdventurer = 0;
    int failedToAddCardToHand = 0;
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    srand(time(0));

    for (i = 0; i < MAX_TESTS; ++i) {

        playerWithCard = -1;

        game = malloc(sizeof(struct gameState));

        randomNewGame(game);

        numPlayers = game->numPlayers;

        randomizeGameState(game);

        for (j = 0; j < numPlayers; ++j) {

            handPos = cardPos(j, 7, game);

            if (handPos != -1) {
                playerWithCard = j;
                break;
            }
        }

        if (playerWithCard != -1) {

            game->whoseTurn = playerWithCard;

            totalDeckSize = game->deckCount[playerWithCard];
            totalDiscardSize = game->discardCount[playerWithCard];
            totalHandSize = game->handCount[playerWithCard];

            totalTreasures += fullDeckCount(playerWithCard, 0, game);
            totalTreasures += fullDeckCount(playerWithCard, 1, game);
            totalTreasures += fullDeckCount(playerWithCard, 2, game);

            cardEffect(7, choice1, choice2, choice3, game, handPos, NULL);
//            refactoredAdventurer(0, playerWithCard, game);

            drawnTreasures += fullDeckCount(playerWithCard, 0, game);
            drawnTreasures += fullDeckCount(playerWithCard, 1, game);
            drawnTreasures += fullDeckCount(playerWithCard, 2, game);

            if (totalTreasures - drawnTreasures != 2) {

                treasureError++;
            }

            if (totalDiscardSize == game->discardCount[playerWithCard]) {

                discardErrors++;
            }
            if (totalHandSize + 1 != game->handCount[playerWithCard]) {

                failedToAddCardToHand++;
            }

            if (game->hand[playerWithCard][handPos] == 7) {

                failedToDiscardAdventurer++;
            }
        }

        free(game);
    }

    totalErrors = discardErrors + drawErrors + failedToAddCardToHand + failedToDiscardAdventurer;
    if(totalErrors > 1){

        printf("A total of %i errors were detected in %i tests.\n",totalErrors, MAX_TESTS);
        printf("Number of times it failed to add 2 treasures: %i\n", treasureError);
        printf("Number of times it failed to discard cards: %i\n", discardErrors);
        printf("Number of times it failed to add cards to hand: %i\n", failedToAddCardToHand);
        printf("Number of times it failed to discard adventurer card: %i\n\n", failedToDiscardAdventurer);

    }else{

        printf("No errors found in %i tests.\n\n", MAX_TESTS);
    }

    return 0;
}