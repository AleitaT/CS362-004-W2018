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

int main (int argc, char** argv) {

	printf("\t **** unittest4 isGameOver() **** \n\n");

	int game = 0;
	time_t t;

	struct gameState *g = malloc(sizeof(struct gameState));
	srand((unsigned) time(&t));

	/**************************************************************
	* OPTION 1 when supply pile is empty game should end
	**************************************************************/	
	g->supplyCount[province] = 0;
	game = isGameOver(g);

	if ( game == 1) {
		printf("\t Success: game ended when privince supply was empoty\n");
	} else {
		printf("\t Failed: game did not end when province supply was empty\n");
	}
	// reset supplyCount
	g->supplyCount[province] = 10;

	/**************************************************************
	* OPTION 2 when three game states are emtpy game should end  
	**************************************************************/
	int i = 0;
	int k = 0;
	int j = 0;
	int randy = 0;
	game = 0;
	int cycles = 10;



	for(i=0; i<cycles; i++){
		//reset all supply cards
		for(k = 0; k < 25; k++) {
			g->supplyCount[k] = 10;
		}
		j=0;
		while(j< 3) {
			randy = rand() % 25;
			if(g->supplyCount[randy] == 0) {
				continue;
			}
			else {
				g->supplyCount[randy] = 0;
				printf("\tSupply %d is empty \n", randy);
				j++;
				continue;
			}
		}
		game = isGameOver(g);
		if(game == 1) {
			printf("\t Success: When three supply piles are empty game ends for 1 instance\n");
		} else {
			printf("\t Failed: A game didn't end when there was three empty supply piles\n");
		}
	}


	printf("\n**** unittest4 isGameOver() complete see above for success/failures ****\n");
	return 0;
}


