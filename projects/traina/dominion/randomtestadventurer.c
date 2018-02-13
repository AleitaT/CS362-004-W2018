#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include "dominion_helpers.h"
#include "dominion.h"
#include "rngs.h"

int error_treasure_count = 0;
int error_shuffle = 0;
int error_deck_hand_count = 0;
int error_draw_card = 0;
int error_card_effect = 0;


void adventurerCardTest(int p, struct gameState *b);

int main() {
	printf("\n **** randomtestdventurer.c **** \n");
	int cycles = 1000; // just to start let's increase once it's working 
	int treasure[] = {gold, silver, copper};
	int treasureCount;
	int i;
	int k;
	int player;
	int error_count;
	// what do we need? 
	// three card min in deck 
	int minimumDeck = 3; 

	struct gameState g;

	srand(time(NULL));

	// initialize game state in a random way 
	for(i = 0; i < cycles; i++) {
		for(k=0; k< sizeof(struct gameState); k++) {
			((char*)&g)[k] = floor(Random() * 256);
		}
		// random player
		player = floor(Random() * MAX_PLAYERS);
		//random deck 
		g.deckCount[player] = floor(Random() * ((MAX_DECK - minimumDeck) + 1) + minimumDeck);
		// random treasures
		treasureCount = floor(Random() * ((g.deckCount[player] - minimumDeck) + 1) + minimumDeck);

		for(i = 0; i<treasureCount; i++) {
			g.deck[player][i] = treasure[rand() % 3];
		}
		g.discardCount[player] = 0;
		g.handCount[player] = floor(Random() * ((MAX_HAND - minimumDeck) + 1) + minimumDeck);
		g.whoseTurn = player;
		adventurerCardTest(player, &g);	
	}
	error_count = error_shuffle + error_deck_hand_count + error_card_effect + error_draw_card + error_treasure_count;
	int passed = cycles - error_count;
	printf("\n **** Passed %d out of %d tests **** \n", passed, cycles);
	return 0;
}

void adventurerCardTest(int player, struct gameState *b) { 

	int a_treasureCount = 0;
	int b_treasureCount = 0;

	int temphand[MAX_HAND];
	int drawntreasure = 0;

	int cardDrawn;
	int card;

	int test_shuffle;
	int test_draw;
	int test_card_effect;

	int i;
	int z = 0;
	int bonus = 0;

	struct gameState a;
	memcpy(&a, b, sizeof(struct gameState));

	// test card effect
	test_card_effect = cardEffect(adventurer, 0, 0, 0, b, 0, &bonus);
	if(test_card_effect) {
		error_card_effect++;
	}

	// mimic adventure card actions here 
	while(drawntreasure < 2) {
		if(a.deckCount[player] < 1) {
			test_shuffle = shuffle(player, &a);
			if(test_shuffle == -1 && a.deckCount[player]>=1) {
				error_shuffle++;
			}
		}
		test_draw = drawCard(player, &a);
		if(test_draw == -1 && a.deckCount[player] != 0) {
			error_draw_card++;
		}
		cardDrawn = a.hand[player][a.handCount[player]-1];
		if(cardDrawn == silver || cardDrawn == copper || cardDrawn == gold) {
			drawntreasure++;
		} else {
			temphand[z] = cardDrawn;
			a.handCount[player]--;
			z++;
		}
	}
	//discard 
	while(z - 1 >= 0) {
		a.discard[player][a.discardCount[player]++] = temphand[z-1]; 
		z = z-1;
	}

	/*  Compare hand counts before and after */
	for(i=0; i < a.handCount[player]; i++){
		card = b -> hand[player][i];
		if(card == copper || card == silver || card == gold) {
			b_treasureCount++;
		}
	}
	for(i = 0; i < b->handCount[player]; i++){
		card = b->hand[player][i];
		if(card == copper || card == silver || card == gold) {
			a_treasureCount++;
		}
	}
	if(b_treasureCount != a_treasureCount) {
		error_treasure_count++;
	}

	int a_handCount = a.handCount[player];
	int a_deckCount = a.deckCount[player];
	int a_discardCount = a.discardCount[player];
	int b_handCount = b->handCount[player];
	int b_deckCount = b->deckCount[player];
	int b_discardCount = b->discardCount[player];
	
	if(!(a_handCount == b_handCount && 
		a_discardCount == b_discardCount && 
		a_deckCount == b_deckCount )) {
		error_deck_hand_count++;
	}
}