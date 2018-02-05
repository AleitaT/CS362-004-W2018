/***************************************************
 *File name: cardtest3.c
 *Author: Jonathan Boese
 *Date: 2/28/2018
 *Description: Testing refactoredSteward function in dominion.c
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
    int totalCoins;
    int playerWithCard;
    int discardErrors = 0;
    int drawErrors = 0;
    int failedToDiscardSteward = 0;
    int failedToAddCardToHand = 0;
    int totalErrors = 0;
    int coinErrors = 0;
    int numChoice1 = 0;
    int numChoice2 = 0;
    int numChoice3 = 0;
    int randomTestChoice;
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    srand(time(0));

    for (i = 0; i < MAX_TESTS; ++i) {

        game = malloc(sizeof(struct gameState));
        playerWithCard = -1;

        randomNewGame(game);

        numPlayers = game->numPlayers;

        randomizeGameState(game);

        for (j = 0; j < numPlayers; ++j) {

            handPos = cardPos(j, 13, game);

            if(handPos!= -1){
                playerWithCard = j;
                break;
            }
        }

        game->whoseTurn = playerWithCard;

        if(playerWithCard != -1){

            totalDeckSize = game->deckCount[playerWithCard];
            totalDiscardSize = game->discardCount[playerWithCard];
            totalHandSize = game->handCount[playerWithCard];
            totalCoins = game->coins;

            choice1 = rand() % (3 + 1 - 1) + 1;

            cardEffect(18, choice1, choice2, choice3, game, handPos, NULL);
//            refactoredSteward(choice1, choice2, choice3, playerWithCard, handPos, game);

            if(choice1 == 1){

                numChoice1++;

                if(totalHandSize + 1 != game->handCount[playerWithCard]){
                    if(game->hand[playerWithCard][handPos] == 18){

                        failedToDiscardSteward++;
                    } else
                    drawErrors++;
                }
            }

            if(choice1 == 2){

                numChoice2++;

                if(totalHandSize - 1 != game->handCount[playerWithCard]){

                    if(game->hand[playerWithCard][handPos] == 18){

                        failedToDiscardSteward++;
                    } else
                        discardErrors++;
                }

                if(totalCoins + 2 != game->coins){
                    coinErrors++;
                }
            }

            if(choice1 > 2){

                numChoice3++;

                if(totalDeckSize != game->deckCount[playerWithCard]){

                    drawErrors++;
                }

                if(totalDiscardSize != game->discardCount[playerWithCard]){

                    discardErrors++;
                }

                if(totalHandSize - 1 <= game->handCount[playerWithCard]){
                    if(game->hand[playerWithCard][handPos] == 18){

                        failedToDiscardSteward++;
                    } else
                        discardErrors++;
                }
            }
        }
        free(game);
    }

    totalErrors = discardErrors + drawErrors + failedToAddCardToHand + failedToDiscardSteward + coinErrors;

    if(totalErrors> 0){

        printf("A total of %i errors were detected in %i tests.\n",totalErrors, MAX_TESTS);
        printf("Number of times it failed to draw a card: %i\n", drawErrors);
        printf("Number of times failed to discard a card: %i\n\t It failed to discard the played card: %i\n",
               discardErrors, failedToDiscardSteward);
        printf("Number of times it failed to add card to hand: %i\n", failedToAddCardToHand);
        printf("Number of times it failed to add coins: %i\n", coinErrors);
        printf("Number of choice 1: %i, choice 2: %i, choice 3: %i\n\n", numChoice1, numChoice2, numChoice3);

    } else

        printf("No errors detected in %i tests.\n\n", MAX_TESTS);



    return 0;
}