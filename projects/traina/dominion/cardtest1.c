/************************************************
* Unit Testing for  Adventurer
*************************************************/

#include "assert.h" 
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "dominion_helpers.h"
#include <string.h>

int main () {

   printf("\n **** CARDTEST1: ADVENTURER **** \n");

   int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse, remodel, tribute, smithy, council_room};
   int i = 0;
   int handPos = 0;
   int choice1 = 0;
   int choice2 = 0;
   int choice3 = 0;
   int bonus = 0;
   int drawn = 2;
   int discard = 1;
   int pass = 1;

   struct gameState g, tester;
   initializeGame(2, kingdomCards, 100, &g);
   memcpy(&tester, &g, sizeof(struct gameState));
   cardEffect(adventurer, choice1, choice2, choice3, &tester, handPos, &bonus);

   /**************************************************************
   * Handcount should go up by 2 for player who plays card
   ****************************************************************/
   int startHandCount = tester.handCount[0];
   int endHandCount = g.handCount[0] + drawn - discard;
   if ( startHandCount != endHandCount) {
      pass = 0;
      printf("\tFailed: Expected hand count after adventurer card to be %d, got %d\n", endHandCount, startHandCount);
   } else {
      printf("\tSuccess: Hand count after playing adventurer is correct(+2)\n");
   }
   
   /*********************************************************
   * Check other players state 
   *********************************************************/
   
   int componentHandStart = tester.handCount[1];
   int componentHandEnd = g.handCount[1];

   if ( componentHandStart != componentHandEnd ) {
      pass = 0;
      printf("\tFailed: Player 2's handcount changed after player 1 played adventurer. Expected %d, got %d\n", componentHandEnd, componentHandStart);
   } else {
      printf("\tSuccess: Player 2's handcount unchanged after player 1 played adventurer\n");
   }


   int componentScoreStart = scoreFor(1, &tester);
   int componentScoreEnd = scoreFor(1, &g);

   if (componentScoreStart != componentScoreEnd) {
      pass = 0;
      printf("\tFailed: Score for player 2 changed when player 1 played adventurer. Expected %d, got %d\n", componentScoreEnd, componentScoreStart);
   } else {
      printf("\tSuccess: Player 2's score unchanged after player 1 played adventurer\n");
   }

   /* check component card pile after playing adventurer */
 
   int componentDeckStart = tester.deckCount[1];
   int componentDeckEnd = g.deckCount[1];
   
   if (componentDeckStart != componentDeckEnd) {
      pass = 0;
      printf("\tFailed: Player 2's deckcount changed after player 1 played adventurer. Expected %d, got %d\n", componentDeckEnd, componentDeckStart);
   } else {
      printf("\tSuccess: Player 2's deckcount unchanged after player 1 played adventurer\n");
   }

   /**********************************************************
   * deckcount should go down by 2 for the 2 cards drawn
   **********************************************************/

   int playerDeckCount = tester.deckCount[0];
   int playerDeckCountDraw = g.deckCount[0] - drawn;
   if (playerDeckCount != playerDeckCountDraw) {
      pass = 0;
      printf("\tFailed: Deck count after playing adventurer was not correct. Expected %d, got %d\n", playerDeckCountDraw, playerDeckCount);
   }
   else {
      printf("\tSuccess: Correct deck count after playing adventurer (-2)\n");
   }


   /**********************************************************
   * score should be the same as before
   **********************************************************/
   int scoreBefore = scoreFor(0, &tester);
   int scoreAfter = scoreFor(0, &g);
   if (scoreBefore != scoreAfter) {
      pass = 0;
      printf("\tFailed: Score after playing adventurer was not correct. Expected %d, got %d\n", scoreAfter, scoreBefore);
   } else {
      printf("\tSuccess: Correct score after playing adventurer (no change)\n");
   }

   /******************************
   * Kingdom Card Piles
   *******************************/
   for (i = 0; i < 10; i++) {
      int testerKindgdom = tester.supplyCount[kingdomCards[i]];
      int gKingdom = g.supplyCount[kingdomCards[i]];
      if (  testerKindgdom!= gKingdom ) {
	     pass = 0;
	     printf("\tFailed: Kingdom card pile #%d did not contain the same number of cards\n", i);
      } else {
	     printf("\tSuccess: Kingdom card pile #%d contained the same number of cards as before\n", i);
      }
   }

   /******************************************************************
   * Tests first two cards taken 
   *****************************************************************/

   int firstCard = tester.hand[0][tester.handCount[0]-1];
   int secondCard = tester.hand[0][tester.handCount[0]-2];

   if (firstCard != copper && firstCard != silver && firstCard != gold) {
      pass = 0;
      printf("\tFailed: First card taken was not a treasure card\n");
   } else {
      printf("\tSuccess: First card = treasure card \n");
   }
   
   if (secondCard != copper && secondCard != silver && secondCard != gold) {
      pass = 0;
      printf("\tFailed: Second card taken was not a treasure card\n");
   } else {
      printf("\tSuccess: Second card = treasure card\n");
   }

   /***********************************
   * Summarize test results 
   ***********************************/
   if (pass) {
      printf("\n **** All Adventurer tests completed with success ****\n\n");
   }
   else {
      printf("\n**** Atleast (1) adventurer test failed ****\n\n");
   }
   return 0;

}