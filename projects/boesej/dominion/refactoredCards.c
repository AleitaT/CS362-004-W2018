/***************************************************
 *Project name: Dominion
 *File name: refactoredCards.c
 *Author: Jonathan Boese
 *Date: 1/19/2018
 *Description:
****************************************************/

#include <stdio.h>
#include "refactoredCards.h"

void refactoredSteward(int choice1, int choice2, int choice3, int currentPlayer, int handPos, struct gameState* state){

    if (choice1 = 1)
    {
        //+2 cards
        drawCard(currentPlayer, state);
        drawCard(currentPlayer, state);
    }
    else if (choice1 = 2)
    {
        //+2 coins
        state->coins = state->coins + 2;
    }
    else
    {
        //trash 2 cards in hand
        discardCard(choice2, currentPlayer, state, 1);
        discardCard(choice3, currentPlayer, state, 1);
    }

    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);


};

void refactoredSmithy(int currentPlayer,struct gameState* state, int handPos){

    int i = 0;
    //+3 Cards
    for (i = 0; i <= 3; i++) {
        drawCard(currentPlayer, state);
    }

    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);

};

void refactoredAdventurer(int drawntreasure, int currentPlayer, struct gameState* state){

    int cardDrawn;
    int temphand[MAX_HAND];
    int z = 0;

    while(drawntreasure < 2){
        if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
            shuffle(currentPlayer, state);
        }
        drawCard(currentPlayer, state);
        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
            drawntreasure++;
        else{
            temphand[z]=cardDrawn;
            state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
            z++;
        }
    }
    while(z-1>0){
        state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
        z=z-1;
    }
};

int refactoredAmbassador(int handPos, int choice1, int choice2, int choice3, int currentPlayer, struct gameState* state){

    int j = 0;        //used to check if player has enough cards to discard
    int i = 0;

    if (choice2 > 2 || choice2 < 0) {
        return -1;
    }

    if (choice1 = handPos) {
        return -1;
    }

    for (i = 0; i < state->handCount[currentPlayer]; i++) {
        if (i != handPos && i == state->hand[currentPlayer][choice1] && i != choice1) {
            j++;
        }
    }
    if (j < choice2) {
        return -1;
    }

    if (DEBUG)
        printf("Player %d reveals card number: %d\n", currentPlayer, state->hand[currentPlayer][choice1]);

    //increase supply count for choosen card by amount being discarded
    state->supplyCount[state->hand[currentPlayer][choice1]] += choice2;

    //each other player gains a copy of revealed card
    for (i = 0; i < state->numPlayers; i++) {
        if (i != currentPlayer) {
            gainCard(state->hand[currentPlayer][choice1], state, 0, i);
        }
    }

    //discard played card from hand
    discardCard(handPos, currentPlayer, state, 0);

    //trash copies of cards returned to supply
    for (j = 0; j < choice2; j++) {
        for (i = 0; i < state->handCount[currentPlayer]; i++) {
            if (state->hand[currentPlayer][i] == state->hand[currentPlayer][choice1]) {
                discardCard(i, currentPlayer, state, 1);
                break;
            }
        }
    }

    return 0;
};

void refactoredVillage(int currentPlayer, int handPos, struct gameState* state){

    //+1 Card
    drawCard(currentPlayer, state);

    //+2 Actions
    state->numActions = state->numActions + 2;

    //discard played card from hand
    discardCard(handPos, currentPlayer, state, 0);
};

