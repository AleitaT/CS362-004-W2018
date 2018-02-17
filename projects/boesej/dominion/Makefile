CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

randomtestcard1: randomtestcard1.c dominion.o
	echo -e "randomtestcard1.c\n" >> randomtestcard1.out
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard1 >> randomtestcard1.out
	echo "refactoredSteward function stats:" >> randomtestcard1.out
	gcov -abcfu dominion.c | sed -n '/refactoredSteward/{n;p;n;p;n;p;n;p}' >> randomtestcard1.out

randomtestcard2: randomtestcard2.c dominion.o
	echo -e "randomtestcard2.c\n" >> randomtestcard2.out
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard2 >> randomtestcard2.out
	echo "refactoredAmbassador function stats:" >> randomtestcard2.out
	gcov -abcfu dominion.c | sed -n '/refactoredAmbassador/{n;p;n;p;n;p;n;p}' >> randomtestcard2.out
	
randomtestadventurer: randomtestadventurer.c dominion.o
	echo -e "randomtestadventurer.c\n" >> randomtestadventurer.out
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer >> randomtestadventurer.out
	echo "refactoredAdventurer function stats:" >> randomtestadventurer.out
	gcov -abcfu dominion.c | sed -n '/refactoredAdventurer/{n;p;n;p;n;p;n;p}' >> randomtestadventurer.out
	
test: unittest1.c dominion.o
	echo -e "Results for running tests:\n" >> unittestresults.out
	echo -e "unittest1.c:\n" >> unittestresults.out
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	
	./unittest1 >> unittestresults.out
	echo "fullDeckCount function stats:" >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/fullDeckCount/{n;p;n;p;n;p;n;p}' >> unittestresults.out 
	
	echo -e "unittest2.c\n" >> unittestresults.out
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	./unittest2 >> unittestresults.out
	echo "updateCoins function stats: " >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/updateCoins/{n;p;n;p;n;p;n;p}' >> unittestresults.out
	
	echo -e "unittest3.c\n" >> unittestresults.out
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	./unittest3 >> unittestresults.out
	echo "scoreFor function stats:" >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/scoreFor/{n;p;n;p;n;p;n;p}' >> unittestresults.out
	
	echo -e "unittest4.c\n" >> unittestresults.out
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	./unittest4 >> unittestresults.out
	echo "supplyCount function stats:" >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/supplyCount/{n;p;n;p;n;p;n;p}' >> unittestresults.out
	
	echo -e "cardtest1.c\n" >> unittestresults.out
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	./cardtest1 >> unittestresults.out
	echo "refactoredSmithy functions stats:" >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/refactoredSmithy/{n;p;n;p;n;p;n;p}' >> unittestresults.out
	
	echo -e "cardtest2.c\n" >> unittestresults.out
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
	./cardtest2 >> unittestresults.out
	echo "refactoredAdventurer functions stats:" >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/refactoredAdventurer/{n;p;n;p;n;p;n;p}' >> unittestresults.out
	
	echo -e "cardtest3.c\n" >> unittestresults.out
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
	./cardtest3 >> unittestresults.out
	echo "refactoredSteard function stats:" >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/refactoredSteward/{n;p;n;p;n;p;n;p}' >> unittestresults.out
		
	echo -e "cardtest4.c\n" >> unittestresults.out
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
	./cardtest4 >> unittestresults.out
	echo "refactoredVillage function stats:" >> unittestresults.out
	gcov -abcfu dominion.c | sed -n '/refactoredVillage/{n;p;n;p;n;p;n;p}' >> unittestresults.out
	

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe randomtestcard1 randomtestcard2 randomtestAdventurer unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
