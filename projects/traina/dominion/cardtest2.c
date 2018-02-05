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
   memcpy(&tester, &g, sizeof(struct gameState));
   cardEffect(council_room, choice1, choice2, choice3, &tester, handPos, &bonus);
   /*******************************************************
	* Other players deck should be reduced by oe
	********************************************************/
   int competitorDeckCountPlay = g.deckCount[1];
   int competitorDeckCountShould = g.deckCount[1] - 1;
   if (competitorDeckCountPlay != competitorDeckCountShould) {
      pass = 0;
      printf("\tFailed: Player 2's deckcount expected %d, got %d after playing council room card.\n", competitorDeckCountShould, competitorDeckCountPlay);
   } else {
      printf("\tSuccess: Player 2's deckcount has -1 after player 1 played council room card.\n");
   }

	/*******************************************************
	* Expect other palyers score to not change
	********************************************************/
   int competitorScorePlay = scoreFor(1, &tester);
   int competitorSscoreShould = scoreFor(1, &g);
   if (competitorScorePlay != competitorSscoreShould) {
      pass = 0;
      printf("\tFailed: Score for player 2 expected %d, got %d for players twos score.\n", competitorSscoreShould, competitorScorePlay);
   } else {
      printf("\tSuccess: Player 2's score unchanged after player 1 played council room room.\n");
   }

	/*******************************************************
	* Expect handcount to go up by 4 for player
	********************************************************/
   int handCountPlay = tester.handCount[0];
   int handCountShould =  g.handCount[0] + drawn - discard;
   if ( handCountPlay != handCountShould) {
      pass = 0;
      printf("\tFailed: Hand count after playing council expected %d, got %d\n", handCountShould, handCountPlay);
   } else {
      printf("\tSuccess: Correct hand count after playing council room (+3)\n");
   }
   
   /*******************************************************
	* Expect number of buys to be incremented by ome
	********************************************************/
   int numBuysPlay = tester.numBuys;
   int numBuysShould = g.numBuys +1;
   if ( numBuysPlay != numBuysShould ) {
      pass = 0;
      printf("\tFailed: Number of buys is incorrect expected %d, got %d\n", numBuysShould, numBuysPlay);
   } else {
      printf("\tSuccess: Correct number of buys after playing council room (+1)\n");
   }

   /*******************************************************
	* expect kingdom card piles to be the same
	********************************************************/
   for (i = 0; i < 10; i++) {
      int kingdomCardsPlay = tester.supplyCount[kingdomCards[i]];
      int kingdomCardsShould = g.supplyCount[kingdomCards[i]];
      if ( kingdomCardsPlay != kingdomCardsShould ) {
         pass = 0;
         printf("\tFAIL: Kingdom card pile #%d did not contain the same number of cards\n", i);
      } else {
         printf("\tSuccess: Kingdom card pile #%d contained the same number of cards as before\n", i);
      }

   }
	/*******************************************************
	* Expect deckcount to go down by 3 
	********************************************************/
   int deckCountPlay = tester.deckCount[0];
   int deckCountShould = g.deckCount[0] - drawn;
   if (deckCountPlay != deckCountShould) {
      pass = 0;
      printf("\tFailed: Deck count after playing council room expected %d, got %d\n", deckCountShould,  deckCountPlay);
   } else {
      printf("\tSuccess: Correct deck count after playing council room (-3)\n");
   }

   /*******************************************************
   * score should be the same 
   ********************************************************/
   int scoreShould =  scoreFor(0, &g);
   int scorePlay = scoreFor(0, &tester);
   if (scoreShould != scorePlay) {
      pass = 0;
      printf("\tFailed: Score after playing council room expected %d, got %d\n", scoreShould, scorePlay);
   } else {
      printf("\tSuccess: Correct score after playing council room (no change)\n");
   }

   	/*******************************************************
	* Expect other player hand size to increase by one
	********************************************************/
   int competitorHandPlay = tester.handCount[1];
   int competitorHandShould = g.handCount[1] + 1;
   if ( competitorHandPlay != competitorHandShould ) {
      pass = 0;
      printf("\tFailed: Player 2's handcount expected %d, got %d\n", competitorHandShould, competitorHandPlay);
   } else {
      printf("\tSuccess: Player 2's handcount has +1 after player 1 played council room\n");
   }

	/*******************************************************
	* Expect victory card piles to be the same
	********************************************************/
   int estateHandPlay = tester.supplyCount[estate];
   int estateHandShould = g.supplyCount[estate];
   if ( estateHandPlay != estateHandShould) {
      pass = 0;
      printf("\tFailed: Number of estate cards expected %d, got %d\n", estateHandPlay, estateHandShould);
   } else {
      printf("\tSuccess: Number of estate cards the same after playing council room\n");
   }
   /*******************************************************
   * Expect duchy card piles to be the same
   ********************************************************/
   int duchyPlay = tester.supplyCount[duchy] ;
   int duchyShould = g.supplyCount[duchy]; 
   if (duchyPlay != duchyShould ) {
      pass = 0;
      printf("\tFailed: Expected %d, got %d duchy cards\n", duchyPlay, duchyShould);
   } else {
      printf("\tSuccess: Number of duchy cards the same after playing council room\n");
   }
   /*******************************************************
   * Expect privince card piles to be the same
   ********************************************************/
   int provincePlay = tester.supplyCount[province];
   int provinceShould = g.supplyCount[province];
   if ( provincePlay != provinceShould ) {
      pass = 0;
      printf("\tFailed: Expected %d, got %d province cards\n", provincePlay,  provinceShould);
   } else {
      printf("\tSuccess: Number of province cards the same after playing council room\n");
   }

   /*******************************************************
	* finally
	********************************************************/

   if (pass) {
      printf("\n **** All CouncilRoom tests completed successfully. **** \n\n");
   } else {
      printf("\n **** Atleast (1) CouncilRoom test failed. **** \n\n");
   }

   return 0;

}