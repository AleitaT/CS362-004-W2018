/************************************************
* Unit Testing for SMITHY
*************************************************/

#include "assert.h" 
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "dominion_helpers.h"
#include <string.h>

int main (int argc, char** argv) {

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

	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int i = 0;
	int discard = 3;
	int drawn = 3;
	int handPos = 0;
	int bonus = 0;
	int pass = 1; // start with fail

	struct gameState g, tester;

	initializeGame(2, kingdomCards, 100, &g);
	printf("\n **** CARDTEST4: SMITHY **** \n\n");

	memcpy(&tester, &g, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &tester, handPos, &bonus);
	

	/*******************************************************
	* Score should be the same 
	********************************************************/
	if(scoreFor(0, &tester) != scoreFor(0, &g)) {
		pass = 0;
		printf("\tFailed: Score after smithy should be %d, got %d\n", scoreFor(0, &g), scoreFor(0, &tester));
	}
	else {
		printf("\tSuccess: Score should not change after playing smithy\n");
	}
	/********************************************************
	* Deck should goo down by 3 
	********************************************************/
	if(tester.deckCount[0] != g.deckCount[0] - drawn) {
		pass = 0;
		printf("\tFailed: Should reduce deck by 3. Expected %d, got %d\n", g.deckCount[0] - drawn, tester.deckCount[0]);
	}
	else {
		printf("\tSuccess: Expected deck count to reduce by 3 after smithy\n");
	}

	/***********************************************************
	* Check hand count after playing smithy 
	***********************************************************/
	if (tester.handCount[0] != g.handCount[0] + drawn - discard) {
		pass = 0;
		printf("\tFailed: Should have hand count of %d, got %d\n", g.handCount[0] + drawn - discard, tester.handCount[0]);
	}
	else {
		printf("\tSuccess: Should have hand count +3 after playing smithy.\n");
	}

	/***********************************************************
	* number of vicctory cards should be the same
	***********************************************************/
   if (tester.supplyCount[estate] != g.supplyCount[estate]) {
      pass = 0;
      printf("\tFailed: Expected number of estate cards to be %d, got %d\n", g.supplyCount[estate], tester.supplyCount[estate]);
   }
   else {
      printf("\tSuccess: Number of estate cards the same after playing smithy\n");
   }

   if (tester.supplyCount[duchy] != g.supplyCount[duchy]) {
      pass = 0;
      printf("\tFailed: Expected number of duchy to be %d, got %d\n", g.supplyCount[duchy], tester.supplyCount[duchy]);
   }
   else {
      printf("\tSuccess: Expected number of duchy cards to be the same after smithy\n");
   }

   if (tester.supplyCount[province] != g.supplyCount[province]) {
      pass = 0;
      printf("\tFailed: Expected number of province to be %d, got %d\n", g.supplyCount[province], tester.supplyCount[province]);
   }
   else {
      printf("\tSuccess: Expected number of province cards to be the same after playing smithy\n");
   }

	/***********************************************************
	* kingdom card piles should be the same
	***********************************************************/
   for (i = 0; i < 10; i++) {
      if (tester.supplyCount[kingdomCards[i]] != g.supplyCount[kingdomCards[i]]) {
	 pass = 0;
	 printf("\tFailed: Kingdom card pile #%d did not contain the same number of cards\n", i);
      }
      else {
	 printf("\tSuccess: Kingdom card pile #%d contained the same number of cards as before\n", i);
      }

   }

	/***********************************************************
	* finally
	***********************************************************/
   if (pass) {
      printf("\n**** All Smithy tests completed successfully ****\n\n");
   }
   else {
      printf("\n **** Atleast (1) smithy test failes **** \n\n");
   }

   return 0;

}
