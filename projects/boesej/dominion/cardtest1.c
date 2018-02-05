/***************************************************
 *File name: cardtest1.c
 *Author: Jonathan Boese
 *Date: 2/28/2018
 *Description: Testing the refactoredSmithy function from dominion.c
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
    int playerWithCard;
    int discardErrors = 0;
    int drawErrors = 0;
    int drawErrorsTooMany = 0;
    int drawErrorsTooFew = 0;
    int failedToDiscardSmithy = 0;
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

            handPos = cardPos(j, 13, game);

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

            cardEffect(13, choice1, choice2, choice3, game, handPos, NULL);
//            refactoredSmithy(playerWithCard, handPos, game);

            if(totalDeckSize - 3 != game->deckCount[playerWithCard]){

                drawErrors++;

                if(totalDeckSize - 3 > game->deckCount[playerWithCard]) {

                    drawErrorsTooMany++;
                }

                if(totalDeckSize + 3 < game->deckCount[playerWithCard]){

                    drawErrorsTooFew++;
                }
            }

            if(totalHandSize + 2 != game->handCount[playerWithCard]){

               failedToAddCardToHand++;
            }

            if(game->hand[playerWithCard][handPos] == 13){

                failedToDiscardSmithy++;
            }
        }

        free(game);
    }

    totalErrors = discardErrors + drawErrors + failedToAddCardToHand + failedToDiscardSmithy;

    if(totalErrors> 0){

        printf("A total of %i errors were detected in %i tests.\n",totalErrors, MAX_TESTS);
        printf("Number of times it failed to draw a card: %i\n", drawErrors);
        printf("Times it drew too many cards: %i\tTimes it drew too few: %i\n", drawErrorsTooMany, drawErrorsTooFew);
        printf("Number of times failed to discard a card: %i\n\t It failed to discard the played card: %i\n",
               discardErrors, failedToDiscardSmithy);
        printf("Number of times it failed to add card to hand: %i\n\n", failedToAddCardToHand);

    } else

        printf("No errors detected in %i tests.\n\n", MAX_TESTS);

    return 0;
}