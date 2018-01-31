/************************************************
* Unit Testing for Council Room 
*************************************************/

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"


int main () {

   int i = 0;
   int choice1 = 0;
   int choice2 = 0;
   int choice3 = 0;
   int drawn = 4;
   int discard = 1;
   int handPos = 0;
   int bonus = 0;
   int pass = 1;

   int kingdomCards[10] = {
   	adventurer, 
   	embargo, 
   	village, 
   	minion, 
   	mine, 
   	cutpurse, 
   	remodel, 
   	tribute, 
   	smithy, 
   	council_room
   };

   struct gameState g, tester;

   initializeGame(2, kingdomCards, 100, &g);

   printf("\n **** CARDTEST2: COUNCIL ROOM **** \n\n");

   	/*******************************************************
	* Other players deck should be reduced by oe
	********************************************************/
   if (tester.deckCount[1] != g.deckCount[1] - 1) {
      pass = 0;
      printf("\tFailed: Player 2's deckcount has incorrect count. Expected %d, got %d\n", g.deckCount[1] - 1, tester.deckCount[1]);
   }
   else {
      printf("\tSuccess: Player 2's deckcount has -1 after player 1 played council room\n");
   }

	/*******************************************************
	* Expect other palyers score to not change
	********************************************************/
   if (scoreFor(1, &tester) != scoreFor(1, &g)) {
      pass = 0;
      printf("\tFailed: Score for player 2 changed when player 1 played council room. Expected %d, got %d\n", scoreFor(1, &g), scoreFor(1, &tester));
   }
   else {
      printf("\tSuccess: Player 2's score unchanged after player 1 played council room\n");
   }

	/*******************************************************
	* Expect handcount to go up by 4 for player
	********************************************************/
   memcpy(&tester, &g, sizeof(struct gameState));

   cardEffect(council_room, choice1, choice2, choice3, &tester, handPos, &bonus);

   if (tester.handCount[0] != g.handCount[0] + drawn - discard) {
      pass = 0;
      printf("\tFailed: Hand count after playing council room was not correct. Expected %d, got %d\n", g.handCount[0] + drawn - discard, tester.handCount[0]);
   }
   else {
      printf("\tSuccess: Correct hand count after playing council room (+3)\n");
   }
   
   	/*******************************************************
	* Expect number of buys to be incremented by ome
	********************************************************/
   if (tester.numBuys != g.numBuys +1) {
      pass = 0;
      printf("\tFailed: Number of buys is incorrect after playing council room. Expected %d, got %d\n", g.numBuys + 1, tester.numBuys);
   }
   else {
      printf("\tSuccess: Correct number of buys after playing council room (+1)\n");
   }


   	/*******************************************************
	* expect kingdom card piles to be the same
	********************************************************/
   for (i = 0; i < 10; i++) {

      if (tester.supplyCount[kingdomCards[i]] != g.supplyCount[kingdomCards[i]]) {
	 pass = 0;
	 printf("\tFAIL: Kingdom card pile #%d did not contain the same number of cards\n", i);
      }
      else {
	 printf("\tSuccess: Kingdom card pile #%d contained the same number of cards as before\n", i);
      }

   }
	/*******************************************************
	* Expect deckcunt to go down by 3 
	********************************************************/
   if (tester.deckCount[0] != g.deckCount[0] - drawn) {
      pass = 0;
      printf("\tFailed: Deck count after playing council room was not correct. Expected %d, got %d\n", g.deckCount[0] - drawn,  tester.deckCount[0]);
   }
   else {
      printf("\tSuccess: Correct deck count after playing council room (-3)\n");
   }


   //Test if the score changed - it should be the same as before
   if (scoreFor(0, &tester) != scoreFor(0, &g)) {
      pass = 0;
      printf("\tFailed: Score after playing council room was not correct. Expected %d, got %d\n", scoreFor(0, &g), scoreFor(0, & tester));
   }
   else {
      printf("\tSuccess: Correct score after playing council room (no change)\n");
   }

   	/*******************************************************
	* Expect other player hand size to increase by one
	********************************************************/
   if (tester.handCount[1] != g.handCount[1] + 1) {
      pass = 0;
      printf("\tFailed: Player 2's handcount has incorrect count. Expected %d, got %d\n", g.handCount[1] + 1, tester.handCount[1]);
   }
   else {
      printf("\tSuccess: Player 2's handcount has +1 after player 1 played council room\n");
   }

	/*******************************************************
	* Expect victory card piles to be the same
	********************************************************/
   if (tester.supplyCount[estate] != g.supplyCount[estate]) {
      pass = 0;
      printf("\tFailed: Number of estate cards differed. Expected %d, got %d\n", g.supplyCount[estate], tester.supplyCount[estate]);
   }
   else {
      printf("\tSuccess: Number of estate cards the same after playing council room\n");
   }

   if (tester.supplyCount[duchy] != g.supplyCount[duchy]) {
      pass = 0;
      printf("\tFailed: Number of duchy cards differed. Expected %d, got %d\n", g.supplyCount[duchy], tester.supplyCount[duchy]);
   }
   else {
      printf("\tSuccess: Number of duchy cards the same after playing council room\n");
   }

   if (tester.supplyCount[province] != g.supplyCount[province]) {
      pass = 0;
      printf("\tFailed: Number of province cards differed. Expected %d, got %d\n", g.supplyCount[province],  tester.supplyCount[province]);
   }
   else {
      printf("\tSuccess: Number of province cards the same after playing council room\n");
   }

   	/*******************************************************
	* finally
	********************************************************/

   if (pass) {
      printf("\n **** All CouncilRoom tests completed successfully. **** \n\n");
   }
   else {
      printf("\n **** Atleast (1) CouncilRoom test failed. **** \n\n");
   }


   return 0;

}