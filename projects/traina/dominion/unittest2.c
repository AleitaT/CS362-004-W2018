/************************************************
* Unit Testing for the function whoseTurn()
*************************************************/

#include "assert.h" 
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int main (int argc, char** argv) {

	struct gameState g;
	int turn = 0;
	int i;
	int s = 0;

	for(i=0; i < 15; i++) {
		g.whoseTurn = turn;
		s = whoseTurn(&g);
		assert(s == turn);
		turn++;
	}
	
	printf("**** unittest2 whoseTurn() unit test passed **** \n");
	return 0;
}


