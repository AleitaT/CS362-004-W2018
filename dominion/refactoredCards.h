/***************************************************
 *Project name: Dominion
 *File name: refactoredCards.h
 *Author: Jonathan Boese
 *Date: 1/19/2018
 *Description:
****************************************************/
#include "dominion_helpers.h"

#ifndef CS362_004_W2018_REFACTOREDCARDS_H
#define CS362_004_W2018_REFACTOREDCARDS_H

void refactoredSteward(int choice1, int choice2, int choice3, int currentPlayer, int handPos, struct gameState* state);

void refactoredSmithy(int currentPlayer, struct gameState* state, int handPos);

void refactoredAdventurer(int drawntreasure, int currentPlayer, struct gameState* state);

int refactoredAmbassador(int handPos, int choice1, int choice2, int choice3, int currentPlayer, struct gameState* state);

void refactoredVillage(int currentPlayer, int handPos, struct gameState* state);

#endif //CS362_004_W2018_REFACTOREDCARDS_H
