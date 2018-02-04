/************************************************
* Unit Testing for getCost() function
*************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "dominion.h"
#include "rngs.h"
#include <time.h>
#include "dominion_helpers.h"

int main(int argc, char** argv){

  printf("\n **** unittest1 getCost() **** \n");

  int i = 0;
  int cost = 0;
  int found = 0;

  for( i = 0; i < 30; i++) {

    cost = getCost(i);

    switch(i) {

      case curse:
        if (cost == 0) {
          printf("\tSuccess: returned cost of 0 for curse card.\n");
        } else {
          found = 1;
          printf("\tFailed: curse card expected cost of 0 received %d\n", cost);
        }
        break;

      case estate:
        if (cost == 2) {
          printf("\tSuccess: returned cost of %d for estate card\n", cost);
        } else {
          found = 1;
          printf("\tFailed: estate card expected cost of 2 received %d\n", cost);
        }
        break;

      case duchy:
        if (cost == 5) {
          printf("\tSuccess: returned cost of %d for duchy card\n", cost);
        } else {
          found = 1;
          printf("\tFailed: duchy card expected cost of 5 received %d\n", cost);
        }
        break;

      case province:
        if (cost == 8) {
          printf("\tSuccess: returned cost of %d for privince card\n", cost);
        } else {
          found = 1;
          printf("\tFailed: privince card expected cost of 8 received %d\n", cost);
        }
        break;

      case copper:
          if (cost == 0) {
          printf("\tSuccess: returned cost of %d for 0 card\n", cost);
        } else {
          found = 1;
          printf("\tFailed: copper card expected cost of 0 received %d\n", cost);
        }
        break;

      case silver:
        if (cost == 3) {
          printf("\tSuccess: returned cost of %d for silver card\n", cost);
        } else {
          found = 1;
          printf("\tFailed: silver card expected cost of 3 received %d\n", cost);
        }
        break;

      case gold:
        if (cost == 6) {
          printf("\tSuccess: returned cost of %d for gold card\n", cost);
        } else {
          found = 1;
          printf("\tFailed: gold card expected cost of 6 received %d\n", cost);
        }
        break;

      case adventurer:
        if (cost == 6) {
          printf("\tSuccess: returned cost of %d for adventurer card\n", cost);
        } else {
          found = 1;
          printf("\tFailed: adventurer card expected cost of 6 received %d\n", cost);
        }
        break;

      case council_room:
        if (cost == 5) {
          printf("\tSuccess: returned cost of %d for council_room card\n", cost);
        } else {
          found = 1;
          printf("\tFailed: council room card expected cost of 5 received %d\n", cost);
        }
        break;

      case feast:
        if ( cost == 4 ){
          printf("\tSuccess: returned cost of %d for feast card\n", cost);
        } else {
          found = 1;
          printf("\tFailed: feast card expected cost of 4 received %d\n", cost);
        }
        break;

      case gardens:
        if (cost == 4) {
          printf("\tSuccess: returned cost of %d for gardens card\n", cost);
        } else {
          found = 1;
          printf("\tFailed: cardens card expected cost of 4 received %d\n", cost);
        }
        break;
        
      case mine:
        if(cost == 5) {
          printf("\tSuccess: returned cost of %d for mine card\n", cost);
        } else {
          found = 1;
          printf("\tFailed: mine card expected cost of 5 received %d\n", cost);
        }
        break;

      case remodel:
        if (cost== 4){
          printf("\tSuccess: returned cost of %d for remodel card\n", cost);
        } else {
          found = 1;
          printf("\tFailed: remodel card expected cost of 4 received %d\n", cost);
        }
        break;
  
      case smithy:
        if ( cost == 4){
          printf("\tSuccess: returned cost of %d for smithy card\n", cost);
        } else {
          found = 1;
          printf("\tFailed: smithy card expected cost of 4 received %d\n", cost);
        }
        break;

      case village:
        if ( cost == 3) {
          printf("\tSuccess: returned cost of %d for village card\n", cost);
        } else {
          found = 1;
          printf("\tFailed: council room card expected cost of 3 received %d\n", cost);
        }
        break;

      case baron:
        if ( cost == 4) {
          printf("\tSuccess: returned cost of %d for baron card\n", cost);
        } else {
          found = 1;
          printf("\tFailed: baron card expected cost of 4 received %d\n", cost);
        }
        break;

      case great_hall:
        if ( cost == 3) {
          printf("\tSuccess: returned cost of %d for great_hall card\n", cost);
        } else {
          found = 1;
          printf("\tFailed: great hall card expected cost of 3 received %d\n", cost);
        }
        break;

      case minion:
        if ( cost == 5) {
          printf("\tSuccess: returned cost of %d for minion card\n", cost);
        } else {
          found = 1;
          printf("\tFailed: minion card expected cost of 5 received %d\n", cost);
        }
        break;

      case steward:
        if ( cost == 3) {
          printf("\tSuccess: returned cost of %d for steward card\n", cost);
        } else {
          found = 1;
          printf("\tFailed: steward card expected cost of 3 received %d\n", cost);
        }
        break;

      case tribute:
        if ( cost == 5) {
          printf("\tSuccess: returned cost of %d for tribute card\n", cost);
        } else {
          found = 1;
          printf("\tFailed: tribute card expected cost of 5 received %d\n", cost);
        }
        break;

      case ambassador:
        if ( cost == 3) {
          printf("\tSuccess: returned cost of %d for ambassador card\n", cost);
        } else {
          found = 1;
          printf("\tFailed: ambassador card expected cost of 3 received %d\n", cost);
        }
        break;

      case cutpurse:
        if(cost == 4){
          printf("\tSuccess: returned cost of %d for cutpurse card\n", cost);
        } else {
          found = 1;
          printf("\tFailed: cutpurse card expected cost of 4 received %d\n", cost);
        }
        break;

      case embargo: 
        if (cost == 2){
          printf("\tSuccess: returned cost of %d for embargo card\n", cost);
        } else {
          found = 1;
          printf("\tFailed: embargo card expected cost of 2 received %d\n", cost);
        }
        break;

      case outpost:
        if( cost == 5) {
          printf("\tSuccess: returned cost of %d for outpost card\n", cost);
        } else {
          found = 1;
          printf("\tFailed: outpost card expected cost of 5 received %d\n", cost);
        }
        break;

      case salvager:
        if ( cost == 4) {
          printf("\tSuccess: returned cost of %d for salvager card\n", cost);
        } else {
          found = 1;
          printf("\tFailed: salvager card expected cost of 4 received %d\n", cost);
        }
        break;

      case sea_hag:
        if(cost == 4) {
          printf("\tSuccess: returned cost of %d for sea_hag card\n", cost);
        } else {
          found = 1;
          printf("\tFailed: sea_hag card expected cost of 4 received %d\n", cost);
        }
        break;

      case treasure_map:
        if(cost == 4) {
          printf("\tSuccess: returned cost of %d for treasure_map card\n", cost);
        } else {
          found = 1;
          printf("\tFailed: treasure map expected cost of 4 received %d\n", cost);
        }
        break;
    }
  }
  if (found) {
    printf("**** unittest1 getCost() found at least (1) error **** \n\n");
  } else {
  printf("**** unittest1 getCost() unittest1 passed with 0 errors **** \n\n");
  }
  return 0;
}


