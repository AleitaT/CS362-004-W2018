/************************************************
* Unit Testing for isGameOver() unit
*************************************************/

#include "assert.h" 
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>
#include "dominion_helpers.h"

int main () {

	struct gameState g;
	int k[10] = {1 ,2, 3, 4, 5, 6, 7, 8, 9, 10};
	int s;

	initializeGame(2, k, 2, &g);
	g.supplyCount[province] = 0;
	s = isGameOver(&g);
	assert(s == 1);
	g.supplyCount[1] = 0;
	g.supplyCount[4] = 0;
	g.supplyCount[7] = 0;
	s = isGameOver(&g);
	assert(s == 1);
	printf("**** unittest4 isGameOver() unit test passed ****\n");
	return 0;
}


