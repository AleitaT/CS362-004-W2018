/***************************************************
 *File name: cardtest4.c
 *Author: Jonathan Boese
 *Date: 2/28/2018
 *Description: Testing refactoredVillage function in dominion.c
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
    int totalDeckSize;
    int totalHandSize;
    int totalDiscardSize;
    int numOfActions;
    int playerWithCard;
    int discardErrors = 0;
    int drawErrors = 0;
    int actionErrors = 0;
    int failedToDiscardVillage = 0;
    int failedToAddCardToHand = 0;
    int totalErrors = 0;
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    srand(time(0));

    for (i = 0; i < MAX_TESTS; ++i) {

        game = malloc(sizeof(struct gameState));
        playerWithCard = -1;

        randomNewGame(game);

        numPlayers = game->numPlayers;

        randomizeGameState(game);

        for (j = 0; j < numPlayers; ++j) {

            handPos = cardPos(j, 14, game);

            if(handPos!= -1){
                playerWithCard = j;
                break;
            }
        }

        game->whoseTurn = playerWithCard;

        if(playerWithCard != -1) {

            totalDeckSize = game->deckCount[playerWithCard];
            totalDiscardSize = game->discardCount[playerWithCard];
            totalHandSize = game->handCount[playerWithCard];
            numOfActions = game->numActions;

            cardEffect(14, choice1, choice2, choice3, game, handPos, NULL);
//            refactoredVillage(playerWithCard, handPos, game);

            if(totalDeckSize - 1 != game->deckCount[playerWithCard]){

                drawErrors++;
            }

            if(totalHandSize != game->handCount[playerWithCard]){

                if(totalHandSize > game->handCount[playerWithCard]){

                    discardErrors++;
                } else if(totalHandSize < game->handCount[playerWithCard] &&
                        totalDeckSize - 1 == game->deckCount[playerWithCard]){

                    failedToAddCardToHand++;
                }
            }

            if(game->hand[playerWithCard][handPos] == 14){

                failedToDiscardVillage++;
            }

            if(numOfActions + 2  != game->numActions){

                actionErrors++;
            }
        }

        free(game);
    }

    totalErrors = actionErrors + discardErrors + drawErrors + failedToAddCardToHand + failedToDiscardVillage;

    if(totalErrors> 0){

        printf("A total of %i errors were detected in %i tests.\n",totalErrors, MAX_TESTS);
        printf("Number of times it failed to draw a card: %i\n", drawErrors);
        printf("Number of times failed to discard a card: %i\n\t It failed to discard the played card: %i\n",
               discardErrors, failedToDiscardVillage);
        printf("Number of times it failed to give player actions: %i\n", actionErrors);
        printf("Number of times it failed to add card to hand: %i\n\n", failedToAddCardToHand);

    } else

        printf("No errors detected in %i tests.\n\n", MAX_TESTS);

    return 0;
}