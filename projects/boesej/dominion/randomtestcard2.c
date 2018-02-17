/***************************************************
 *File name: randomtestcard2.c
 *Author: Jonathan Boese
 *Date: 2/18/2018
 *Description: Testing the refactoredAmbassador function from dominion.c
****************************************************/


#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define MAX_TESTS 30000

int enoughToDiscard(int choice1, struct gameState* state, int currentPlayer, int handPos){

    int i, j = 0;

    for (i = 0; i < state->handCount[currentPlayer]; i++) {
        if (i != handPos && state->hand[currentPlayer][i] == state->hand[currentPlayer][choice1]) {
            j++;
        }
    }

    return j;
}

int main(){

    struct gameState* game;
    int i,j,k,l;
    int numPlayers;
    int totalHandSize;
    int totalSupply;
    int exitCode;
    int playerWithCard;
    int choiceFailure;
    int discardErrors = 0;
    int failedToDiscardAmbassador = 0;
    int totalErrors = 0;
    int exitsCorrectly = 0;
    int exitsFails = 0;
    int testPlayer = 0;
    int testPlayerCards = 0;
    int failureToAddToOthers = 0;
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0;
    srand(time(0));

    for (i = 0; i < MAX_TESTS; ++i) {

        game = malloc(sizeof(struct gameState));
        playerWithCard = -1;

        randomNewGame(game);

        numPlayers = game->numPlayers;

        randomizeGameState(game);

        for (j = 0; j < numPlayers; ++j) {

            handPos = cardPos(j, 20, game);

            if (handPos != -1) {
                playerWithCard = j;
                break;
            }
        }
        if(playerWithCard != -1) {

            choice1 = rand() % (game->handCount[playerWithCard]);

            while (game->hand[playerWithCard][choice1] != 20) {

                choice1 = rand() % (game->handCount[playerWithCard]);
            }

            choice2 = rand() % 5;

            choiceFailure = enoughToDiscard(choice1, game, playerWithCard, handPos);

            if (choiceFailure <= choice2) {

                game->whoseTurn = playerWithCard;
                totalSupply = game->supplyCount[choice1];
                testPlayerCards = enoughToDiscard(choice1, game, testPlayer, -1);

                if (playerWithCard + 1 > numPlayers) {

                    testPlayer = playerWithCard - 1;
                } else {

                    testPlayer = playerWithCard + 1;
                }


                totalHandSize = game->handCount[playerWithCard];

//                exitCode = cardEffect(ambassador, choice1, choice2, choice3, game, handPos, NULL);
                exitCode = refactoredAmbassador(handPos, choice1, choice2, choice3, playerWithCard, game);

                if (choice2 < 3 && choice2 > 0) {

                    if (totalHandSize - choice2 > game->handCount[playerWithCard]) {

                        discardErrors++;
                    }

                    if (game->hand[playerWithCard][handPos] == 20) {

                        failedToDiscardAmbassador++;
                    }
                }

                if (choice2 > 2 || choice2 < 0) {
                    if (exitCode == -1) {
                        exitsCorrectly++;
                    }

                    if (exitCode != -1) {
                        exitsFails++;
                    }
                }

                if (enoughToDiscard(choice1, game, testPlayer, -1) <= testPlayerCards ||
                    totalSupply - (numPlayers - 1) != game->supplyCount[choice1]) {

                    failureToAddToOthers++;
                }

            }
        }

        free(game);
    }

    totalErrors = discardErrors + failedToDiscardAmbassador + exitsCorrectly + exitsFails + failureToAddToOthers;

    if(totalErrors> 0){

        printf("A total of %i errors were detected in %i tests.\n",totalErrors, MAX_TESTS);
        printf("Number of times failed to discard a card: %i\n\t It failed to discard the played card: %i\n",
               discardErrors, failedToDiscardAmbassador);
        printf("Number of times it failed to add card to other players hand: %i\n", failureToAddToOthers);
        printf("Number of times it failed to exit correctly: %i\n\n", exitsCorrectly);

    } else

        printf("No errors detected in %i tests.\n\n", MAX_TESTS);

    return 0;
}