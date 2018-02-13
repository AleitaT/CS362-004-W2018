/************************************************
* Unit Testing for refactored buyCard()
*************************************************/

#include "assert.h" 
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int main (int argc, char** argv) {
	struct gameState g;
	int k[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int s;

	initializeGame(2, k, 2, &g);
	g.numBuys = 0;
	s = buyCard(5, &g);
	assert(s == -1);
	g.numBuys = 5;
	g.coins = 0;
	s = buyCard(5, &g);
	assert(s == -1);
	g.coins = 100;
	s = buyCard(5, &g);
	assert(s == 0);

	printf("**** unittest3 buyCard() unit test passed **** \n");
	return 0;
}


