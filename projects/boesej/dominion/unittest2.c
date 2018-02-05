/***************************************************
 *File name: unittest2.c
 *Author: Jonathan Boese
 *Date: 2/28/2018
 *Description: Testing the function updateCoins from dominion.c
****************************************************/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define MAX_TESTS 1000

int main(){

    struct gameState* game;
    int numbPlayers = 0;
    int randomPlayer = 0;
    int bonus = 0;
    int coins;
    int i,j,k,l;
    int errors = 0;
    srand(time(0));

    for (i = 0; i < MAX_TESTS; ++i) {

        game = malloc(sizeof(struct gameState));
        coins = 0;
        bonus = rand() % (100 + 1 - 0) + 0;
        coins += bonus;

        randomNewGame(game);

        numbPlayers = game->numPlayers;

        randomizeGameState(game);

        randomPlayer = rand() % (numbPlayers + 1 - 2) + 2;

        for (j = 0; j < game->handCount[randomPlayer] ; ++j) {

            if(game->hand[randomPlayer][j] == 4){
                coins++;
            }else if(game->hand[randomPlayer][j] == 5){
                coins += 2;
            }else if(game->hand[randomPlayer][j] == 6){
                coins += 3;
            }
        }

        updateCoins(randomPlayer, game, bonus);

        if(coins != game->coins){

            printf("Calculated coins in player %i's hand: %i, functions calculation: %i\n",numbPlayers, coins, game->coins);
            errors++;
        }
        free(game);
    }

    printf("%i tests ran. Encountered %i errors!\n\n", MAX_TESTS, errors);
    return 0;
}