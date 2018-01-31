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

   printf("\n **** CARDTEST1: ADVENTURER **** \n");


   /**************************************************************
   * Handcount should go up by 2 for player who plays card
   ****************************************************************/
   memcpy(&tester, &g, sizeof(struct gameState));

   cardEffect(adventurer, choice1, choice2, choice3, &tester, handPos, &bonus);

   if (tester.handCount[0] != g.handCount[0] + drawn - discard) {
      pass = 0;
      printf("\tFailed: Hand count after playing adventurer was not correct. Expected %d, got %d\n", g.handCount[0] + drawn - discard, tester.handCount[0]);
   }
   else {
      printf("\tSuccess: Correct hand count after playing adventurer (+2)\n");
   }
   
   /*********************************************************
   * Check other players state 
   *********************************************************/
   if (tester.handCount[1] != g.handCount[1]) {
      pass = 0;
      printf("\tFailed: Player 2's handcount changed after player 1 played adventurer. Expected %d, got %d\n", g.handCount[1], tester.handCount[1]);
   }
   else {
      printf("\tSuccess: Player 2's handcount unchanged after player 1 played adventurer\n");
   }

   if (tester.deckCount[1] != g.deckCount[1]) {
      pass = 0;
      printf("\tFailed: Player 2's deckcount changed after player 1 played adventurer. Expected %d, got %d\n", g.deckCount[1], tester.deckCount[1]);
   }
   else {
      printf("\tSuccess: Player 2's deckcount unchanged after player 1 played adventurer\n");
   }

   if (scoreFor(1, &tester) != scoreFor(1, &g)) {
      pass = 0;
      printf("\tFailed: Score for player 2 changed when player 1 played adventurer. Expected %d, got %d\n", scoreFor(1, &g), scoreFor(1, &tester));
   }
   else {
      printf("\tSuccess: Player 2's score unchanged after player 1 played adventurer\n");
   }


   /**********************************************************
   * deckcount should goe down by 2 for the 2 cards drawn
   **********************************************************/
   if (tester.deckCount[0] != g.deckCount[0] - drawn) {
      pass = 0;
      printf("\tFailed: Deck count after playing adventurer was not correct. Expected %d, got %d\n", g.deckCount[0] - drawn, tester.deckCount[0]);
   }
   else {
      printf("\tSuccess: Correct deck count after playing adventurer (-2)\n");
   }

   //Test if the score changed - it should be the same as before
   if (scoreFor(0, &tester) != scoreFor(0, &g)) {
      pass = 0;
      printf("\tFailed: Score after playing adventurer was not correct. Expected %d, got %d\n", scoreFor(0, &g), scoreFor(0, &tester));
   }
   else {
      printf("\tSuccess: Correct score after playing adventurer (no change)\n");
   }

   /******************************
   * Kingdom Card Piles
   *******************************/
   for (i = 0; i < 10; i++) {

      if (tester.supplyCount[kingdomCards[i]] != g.supplyCount[kingdomCards[i]]) {
	 pass = 0;
	 printf("\tFailed: Kingdom card pile #%d did not contain the same number of cards\n", i);
      }
      else {
	 printf("\tSuccess: Kingdom card pile #%d contained the same number of cards as before\n", i);
      }
   }

   /*************************************
   * Tests first two cards taken 
   **************************************/
   if (tester.hand[0][tester.handCount[0]-1] != copper && tester.hand[0][tester.handCount[0]-1] != silver && tester.hand[0][tester.handCount[0]-1] != gold) {
      pass = 0;
      printf("\tFailed: First card taken was not a treasure card\n");
   }
   else {
      printf("\tSuccess: First card = treasure card \n");
   }
   
   if (tester.hand[0][tester.handCount[0]-2] != copper && tester.hand[0][tester.handCount[0]-2] != silver && tester.hand[0][tester.handCount[0]-2] != gold) {
      pass = 0;
      printf("\tFailed: Second card taken was not a treasure card\n");
   }
   else {
      printf("\tSuccess: Second card = treasure card\n");
   }

   /**************************************************
   * Number of victory cards piles should be the same
   ***************************************************/
   if (tester.supplyCount[estate] != g.supplyCount[estate]) {
      pass = 0;
      printf("\tFailed: Number of estate cards differed. Expected %d, got %d\n", g.supplyCount[estate], tester.supplyCount[estate]);
   }
   else {
      printf("\tSuccess: Number of estate cards the same after playing adventurer\n");
   }

   if (tester.supplyCount[duchy] != g.supplyCount[duchy]) {
      pass = 0;
      printf("\tFailed: Number of duchy cards differed. Expected %d, got %d\n", g.supplyCount[duchy], tester.supplyCount[duchy]);
   }
   else {
      printf("\tSuccess: Number of duchy cards the same after playing adventurer\n");
   }

   if (tester.supplyCount[province] != g.supplyCount[province]) {
      pass = 0;
      printf("\tFailed: Number of province cards differed. Expected %d, got %d\n", g.supplyCount[province], tester.supplyCount[province]);
   }
   else {
      printf("\tSuccess: Number of province cards the same after playing adventurer\n");
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