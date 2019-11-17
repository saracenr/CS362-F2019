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

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o cardFunctions.o $(CFLAGS)

randomtest1: randomtestcard1.c dominion.o rngs.o cardFunctions.o
	gcc  -o randomtest1 -g  randomtestcard1.c dominion.o rngs.o cardFunctions.o $(CFLAGS)

randomtest2: randomtestcard2.c dominion.o rngs.o cardFunctions.o
	gcc  -o randomtest2 -g  randomtestcard2.c dominion.o rngs.o cardFunctions.o $(CFLAGS)

randomtest3: randomtestcard3.c dominion.o rngs.o cardFunctions.o
	gcc  -o randomtest3 -g  randomtestcard3.c dominion.o rngs.o cardFunctions.o $(CFLAGS)

randomtests: randomtest1 randomtest2 randomtest3

randomtestresults: randomtests
	randomtest1 &> randomtestresults.out
	randomtest2 &> randomtestresults.out
	randomtest3 &> randomtestresults.out
	gcov cardFunctions.c -b -f >> randomtestresults.out
	cat cardFunctions.c.gcov >> randomtestresults.out

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe randomtest1 randomtest2 randomtest3
