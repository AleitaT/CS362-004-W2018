/************************************************
* Unit Testing for getCost function
*************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "dominion.h"
#include "rngs.h"
#include <time.h>

int main(int argc, char** argv){
  int a = getCost(0);
  assert(a == 0);
  int b = getCost(adventurer);
  assert(b == 6);
  int c = getCost(village);
  assert(c == 3);
  int d = getCost(baron);
  assert(d == 4);
	printf("**** unittest1 getCost() unit test passed **** \n");
	return 0;
}


