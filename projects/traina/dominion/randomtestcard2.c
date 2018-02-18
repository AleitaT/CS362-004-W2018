#include "dominion.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "dominion_helpers.h"
#include "rngs.h"

int error_deck_hand_count = 0;
int error_buys = 0;
int error_p2_deck_hand_count = 0;
int error_card_effect = 0;
int error_discard_card = 0;
int error_draw_card = 0;

void test_council_room(int p, struct gameState *b);
int isEqual(int left, int right);

int main () {

    printf(" ----------- testing randomcardtest2.c ------------\n");
    printf(" ----------- testing council_roomCard() -----------\n");

    int i, j, k;
    int player;
    int deckCount;
    int handCount; 
    int discardCount;
    int num_players[] = {2,3,4};

    struct gameState g;

    srand(time(NULL));

    int cycles = 50000;

    /* randomly initialize game state like we did in adventurer random test*/
    for (i = 0; i < cycles; i++) {
        int gameSize = sizeof(struct gameState);

        for (j = 0; j < gameSize; j++) {
            int randomValue = floor(Random() * 256);
            ((char*)&g)[j] = randomValue;
        }
        /* determine the random values needed to fill the game */
        int third = rand() %3;
        int randomDeck = floor(Random() * (MAX_DECK-1));
        int randomDeck2 = floor(Random() * (MAX_DECK));
        int randomHand = floor(Random() * MAX_HAND);
        /* use those values to determine game state */
        g.numPlayers = num_players[third];
        g.numBuys = 1;
        g.playedCardCount = randomDeck;
        player = g.numPlayers - 2;
        deckCount = randomDeck2;
        handCount = randomHand;
        discardCount = randomDeck2;
        g.whoseTurn = player;
        
        /* set up others players hand */
        for (k = 0; k < g.numPlayers; k++) {
            g.deckCount[k] = deckCount;
            g.handCount[k] = handCount;
            g.discardCount[k] = discardCount;
        }
        test_council_room(player,&g);
    }
    int error_total =   error_card_effect + 
                        error_discard_card + 
                        error_draw_card + 
                        error_deck_hand_count + 
                        error_buys;

    if (error_total == 0) {
        printf ("!--------------- SUCCESS ALL TESTS PASSED ----------------!\n\n");
    }
    else {
        printf("\nError: function drawCard() failed %d times.\n", error_draw_card);
        printf ("!-------------------------------------------------!\n\n");
        printf("Error: function cardEffect() failed %d times.\n", error_card_effect);
        printf ("!-------------------------------------------------!\n\n");       
        printf("Error: function discardCard() failed %d times.\n", error_discard_card);
        printf ("!-------------------------------------------------!\n\n");
        printf("Error: function numBuys Count mismatch %d times.\n", error_buys);
        printf ("!-------------------------------------------------!\n\n");
        printf("Error: function player 2's hand and deck count did not match %d times.\n", error_p2_deck_hand_count);
        printf ("!-------------------------------------------------!\n\n");
        printf("Error: player's hand and deck count didn't match %d times.\n", error_deck_hand_count);
    }
    printf ("\n\n Ceverage Report Below... \n");
    return 0;
}
/****************************************************
* council room test function 
* received an int and a game struct 
*****************************************************/
void test_council_room(int p, struct gameState *b) {
  int choice1 = 1;
  int choice2 = 1;
  int choice3 = 1;
  int handPos = 1;
  int i;
  int bonus = 0;
  struct gameState a;
  memcpy(&a,b,sizeof(struct gameState));      // duplicate our game state

  // this is failing -- did some digging and I had a break instead of a return after the 
  // refactored function call. Resolved.
  int test_card_effect = cardEffect(council_room, choice1, choice2, choice3, b, handPos, &bonus);

  // call draw card 4 times
  int draw1 = drawCard(p,&a);
  int draw2 = drawCard(p,&a);
  int draw3 = drawCard(p,&a);
  int draw4 = drawCard(p,&a);

  a.numBuys++;

  /* players draw cards, check if they are equal */
  for (i = 0; i < a.numPlayers; i++) {
      if (i != p) {
          int test_draw = drawCard(i,&a);
          if ((isEqual(test_draw, -1)) && !(isEqual(a.deckCount[i], 0))) {
              error_draw_card++;
          }
      }
  }

  /* discard cards */ 
  int test_discard = discardCard(0, p, &a, 0);

  /* grab the deck and hand counts for
   * game state a and game state b */
  int b_hand_count = b->handCount[p];
  int b_deck_count = b->deckCount[p];
  int a_hand_count = a.handCount[p];
  int a_deck_count = a.deckCount[p];

  /* compare number of buys */
  if (!(isEqual(a.numBuys, b->numBuys))) {
      error_buys++;
  }

  /* Check all four draw cards */
  if ((isEqual(draw1, -1)) && !(isEqual(a.deckCount[p], 0))) {
      error_draw_card++;
  }
  if ((isEqual(draw2, -1)) && !(isEqual(a.deckCount[p], 0))) {
      error_draw_card++;
  }
  if ((isEqual(draw3, -1)) && !(isEqual(a.deckCount[p], 0))) {
      error_draw_card++;
  }
  if ((isEqual(draw4, -1)) && !(isEqual(a.deckCount[p], 0))) {
      error_draw_card++;
  }
  // check if cardeffect or discardCard failed
  if (!(test_card_effect == 0 && test_discard == 0)) {
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
  // check if the other players hand and deck counts match
  for (i = 0; i < a.numPlayers; i++) {
    if (!(isEqual(i,p))) {
      if (!(isEqual(b->handCount[i],a.handCount[i]) && isEqual(b->deckCount[i], a.deckCount[i]))) {
        error_p2_deck_hand_count++;
      }
    }
  }
}

int isEqual(int left, int right) {
    if(left!=right) {
    //  printf("Error: value %d is not equal to %d", left, right);
        return 0;
    } else {
        return 1;
    }
}