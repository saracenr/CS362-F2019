CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

cardFunctions.o: cardFunctions.h cardFunctions.c
	gcc -c cardFunctions.c -g $(CFLAGS)

playdom: dominion.o playdom.c cardFunctions.o
	gcc -o playdom playdom.c -g dominion.o rngs.o cardFunctions.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o cardFunctions.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o cardFunctions.o $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o cardFunctions.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o cardFunctions.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o cardFunctions.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o cardFunctions.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o cardFunctions.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o cardFunctions.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o cardFunctions.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o cardFunctions.o $(CFLAGS)

unittest5: unittest5.c dominion.o rngs.o cardFunctions.o
	gcc -o unittest5 -g  unittest5.c dominion.o rngs.o cardFunctions.o $(CFLAGS)

unittestBug5: unittestBug5.c dominion.o rngs.o cardFunctions.o
	gcc -o unittestBug5 -g  unittestBug5.c dominion.o rngs.o cardFunctions.o $(CFLAGS)

unittestBug6: unittestBug6.c dominion.o rngs.o cardFunctions.o
	gcc -o unittestBug6 -g  unittestBug6.c dominion.o rngs.o cardFunctions.o $(CFLAGS)

unittestBug7: unittestBug7.c dominion.o rngs.o cardFunctions.o
	gcc -o unittestBug7 -g  unittestBug7.c dominion.o rngs.o cardFunctions.o $(CFLAGS)

unittestBug8: unittestBug8.c dominion.o rngs.o cardFunctions.o
	gcc -o unittestBug8 -g  unittestBug8.c dominion.o rngs.o cardFunctions.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o cardFunctions.o $(CFLAGS)

all: playdom player 

unittests: unittest1 unittest2 unittest3 unittest4 unittest5

unittestresults: unittests
	./unittest1 &> unittestresult.out
	./unittest2 &> unittestresult.out
	./unittest3 &> unittestresult.out
	./unittest4 &> unittestresult.out
	./unittest5 &> unittestresult.out
	gcov cardFunctions.c -b -f >> unittestresult.out
	cat cardFunctions.c.gcov >> unittestresult.out


clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1 unittest2 unittest3 unittest4 unittest5 unittestBug5 unittestBug6 unittestBug7 unittestBug8
