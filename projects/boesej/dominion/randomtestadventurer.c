   
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int error_treasure_count = 0;
int error_shuffle = 0;
int error_deck_hand_count = 0;
int error_draw_card = 0;
int error_card_effect = 0;
int error_count = 0;


void testAdventurerCard(int p, struct gameState *b);
int isTreasure(int c);
int isEqual(int l, int r);

int main () {
    printf(" ----------- testing randomtestadventurer.c ------------\n");
    printf(" ---------------- testing adventurer card ---------------\n");
    int treasure[] = {silver, copper, gold};
    int treasure_count;
    int i, j, player;
    struct gameState g;
    int min = 3;
    //seed for random
    srand(time(NULL));
    int cycles = 100000; // having memory issues over 450 slows down which is conveniently where it starts getting a high fail rate


    for (i = 0; i < cycles; i++) {
      for (j = 0; j < sizeof(struct gameState); j++) {
        // randomly initialize game state for each iteration
        ((char*)&g)[j] = floor(Random() * 256);
      }
      // select a random player from max player and set up cards
      player = floor(Random() * MAX_PLAYERS);;
      g.deckCount[player] = floor(Random() * ((MAX_DECK - min) + 1) + min);;
      treasure_count = floor(Random() * ((g.deckCount[player] - min) + 1) + min);;

      // lets make sure there are at least three treasure cards available in deck 
      for (j = 0; j < treasure_count; j++) {
        g.deck[player][j] = treasure[rand() % 3];
      }
      g.handCount[player] = floor(Random() * ((MAX_HAND - min) + 1) + min);
      g.whoseTurn = player;
      g.discardCount[player] = 0;

      // test adventure card function to go here... 
      // take game struct and player
      testAdventurerCard(player, &g);
    }
    // get an error total from everything collected/compared for clearer reporting
    // should we break this out for better error reporting? 
    int error_total = error_card_effect + 
    									error_draw_card + error_shuffle +
                    	error_deck_hand_count + 
                    	error_treasure_count;
    // report your findings 
    if (error_total == 0) {
        printf ("***** Passed all tests in randomtestadventurer.c *****\n");
    }

    else {
        printf("\nFailure: tests failed for atleast (1) test in randomtestadventurer.c *****\n");
        printf ("-------------------------------------------------\n");       
        printf("Error: cardEffect() failed: %d\n", error_card_effect);
        printf ("-------------------------------------------------\n");       
        printf("Error: Treasure Count mismatch: %d\n", error_treasure_count);
        printf ("-------------------------------------------------\n");       
        printf("Error: shuffle() failed: %d\n", error_shuffle);
        printf ("-------------------------------------------------\n");       
        printf("Error: drawCard() failed: %d\n", error_draw_card);
        printf ("-------------------------------------------------\n");       
        printf("Error: Hand/Deck Count mismatch: %d\n", error_deck_hand_count);
        printf ("-------------------------------------------------\n");       
    }
    return 0;
}

void testAdventurerCard(int p, struct gameState *b) {

    // define 'state' varaibles for game structs 
    int temphand[MAX_HAND];
    int card;
    int bonus = 0;
    int drawntreasure = 0;
    int cardDrawn;
    int i;
    int z = 0;
    
    int test_card_effect;
    int test_shuffle;
    int test_draw;

    int a_treasure_count = 0;
    int b_treasure_count = 0;

    // make your dupe game for testing and comparing to actual 
    struct gameState a;
    memcpy(&a,b,sizeof(struct gameState));

    // easy peasy test card effect.... or is it?  what have I don't wrong here.  
    // come back afte ryou write other tests. memory leak?  freaking out goes from 44 to 1241 beween 400 - 470 cycles
    test_card_effect = cardEffect(adventurer,0,0,0,b,0,&bonus);
    if (test_card_effect) {
        error_card_effect++;
    }

    // we should mmic the effects of fhe adventurer card and see if 
    // that is what our adventurer actionc play has as well. 
    while(drawntreasure < 2) {
      if (a.deckCount[p] < 1) {
        // shuffle check 
        test_shuffle = shuffle(p, &a);
        if (test_shuffle == -1 && a.deckCount[p] >= 1) {
          error_shuffle++;
        }
      }
      // draw card check 
      test_draw = drawCard(p, &a);
      if (test_draw == -1 && a.deckCount[p] != 0) {
          error_draw_card++;
      }
      // ccheck out top card p--- is treasure? 
      cardDrawn = a.hand[p][a.handCount[p] - 1];
      if (isTreasure(cardDrawn)) {
        drawntreasure++;
      } else {
        temphand[z] = cardDrawn;
        a.handCount[p]--; 
        z++;
      }
    }
    while(z - 1 >= 0) {
      a.discard[p][a.discardCount[p]++] = temphand[z - 1]; 
      z = z - 1;
    }

    // check a hand counts for treasures
    for (i = 0; i < a.handCount[p]; i++) {
      card = a.hand[p][i];
      if (isTreasure(card)) {
          a_treasure_count++;
      }
    }
    // check b hand counts for treasures
    for (i = 0; i < b->handCount[p]; i++) {
      card = b->hand[p][i];
      if (isTreasure(card)) {
          b_treasure_count++;
      }
    }
    // treasures for a and b should match up 
    if (!(isEqual(b_treasure_count, a_treasure_count))) {
      error_treasure_count++;
    }

    // a game hand and deck counts
    int a_hand = a.handCount[p];
    int a_deck = a.deckCount[p];
    int a_discard = a.discardCount[p];
    // b game hand and deck counts
    int b_hand = b->handCount[p];
    int b_deck = b->deckCount[p];
    int b_discard = b->discardCount[p];


    // hand and deck counts should of course be the same -- wrap but separate later if you have time 
    if (!(isEqual(b_hand, a_hand) && isEqual(b_deck, a_deck) && isEqual(b_discard, a_discard))) {
      error_deck_hand_count++;
    }
}

// helper functions -- maybe we can do more with these later. 
int isTreasure(int card) {
  if(card == copper || card == gold || card == silver) {
    return 1;
  } else {
    return 0;
  }
}

int isEqual(int left, int right) {
  if(left!=right) {
    return 0;
  } else {
    return 1;
  }
}