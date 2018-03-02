/***********************************************
* Random test for 
* 
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

// fail counter variables
int error_card_effect = 0;
int error_discard_card = 0;
int error_draw_card = 0;
int error_deck_hand_count = 0;

void test_smithy(int p, struct gameState *b);
int isEqual(int left, int right);

int main () {
    printf(" ----------- testing randomcardtest2.c ------------\n");
    printf(" ----------- testing smithy card -----------\n");

    int iterations = 10000;
    int i, j, player;
    struct gameState g;
    srand(time(NULL));

    // randomly initialized the game state
    for (i = 0; i < iterations; i++) {
        for (j = 0; j < sizeof(struct gameState); j++) {
            ((char*)&g)[j] = floor(Random() * 256);
        }
        /* get the random values we need for our game */
        int randomPlayer = floor(Random() * MAX_PLAYERS);
        int randomDeckCount = floor(Random() * MAX_DECK);
        int randomHand = floor(Random() * MAX_HAND);
        int randomCardCount = floor(Random() * (MAX_DECK-1));
       	/* apply the random values to the game */
        player = randomPlayer;
        g.deckCount[player] = randomDeckCount;
        g.discardCount[player] = randomDeckCount;
        g.handCount[player] = randomHand;
        g.playedCardCount = randomCardCount;
        g.whoseTurn = player;

        test_smithy(player,&g);
    }
    int error_total = error_card_effect + 
    								error_discard_card +
                    error_draw_card + 
                    error_deck_hand_count;

    if (error_total == 0) {
       printf ("!--------------- SUCCESS ALL TESTS PASSED ----------------!\n\n");
    }
     else {
      printf("Error: function discardCard() failed %d times.\n", error_discard_card);
      printf ("!-------------------------------------------------!\n\n");
      printf("Error: player's hand and deck count didn't match %d times.\n", error_deck_hand_count);
      printf("\nError: function drawCard() failed %d times.\n", error_draw_card);
      printf ("!-------------------------------------------------!\n\n");
      printf("Error: function cardEffect() failed %d times.\n", error_card_effect);
      printf ("!-------------------------------------------------!\n\n");       

  }
  return 0;
}

void test_smithy(int p, struct gameState *b) {
    int test_card_effect;
    int test_discard;
    int draw1;
    int draw2;
    int draw3;
  	int choice1 = 1;
  	int choice2 = 1;
  	int choice3 = 1;
  	int handPos = 1;
    int bonus = 0;

    struct gameState a;

    memcpy(&a,b,sizeof(struct gameState));
   	test_card_effect = cardEffect(smithy, choice1, choice2, choice3, b, handPos, &bonus);

    draw1 = drawCard(p,&a);
    draw2 = drawCard(p,&a);
    draw3 = drawCard(p,&a);
    test_discard = discardCard(0, p, &a, 0);
    int a_hand_count = a.handCount[p];
    int a_deck_count = a.deckCount[p];
    int b_hand_count = b->handCount[p];
    int b_deck_count = b->deckCount[p];

    if ((isEqual(draw1, -1))  && !(isEqual(a.deckCount[p], 0))) {
        error_draw_card++;
    }
    if ((isEqual(draw2, -1)) && !(isEqual(a.deckCount[p], 0))) {
        error_draw_card++;
    }
    if ((isEqual(draw3, -1)) && !(isEqual(a.deckCount[p], 0))) {
        error_draw_card++;
    }
    if (!(isEqual(test_card_effect, 0) && isEqual(test_discard, 0))) {
        if (test_card_effect) {
            error_card_effect++;
        }
        if (test_discard) {
            error_discard_card++;
        }
    }
    // check if the hand and deck counts dont match up
    if (!(isEqual(b_hand_count, a_hand_count) && isEqual(b_deck_count, a_deck_count))) {
        error_deck_hand_count++;
    }
}

int isEqual(int left, int right) {
  if(left!=right) {
    //printf("Error: value %d is not equal to %d", left, right);
    return 0;
  } else {
    return 1;
  }
}