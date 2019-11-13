#include "dominion.h"
#include "dominion_helpers.h"
#include "cardFunctions.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    int i;
    int seed = 1000;
    int numPlayer;
    int currentPlayer;
    int maxBonus = 10;
    int p, r, handCount, runTime, choiceOne;
    int estateLocation;
    int baronLocation;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    int possibleCards[16] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall, copper, silver, gold, estate, duchy, province};
    struct gameState G;
    int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    for (runTime = 0; runTime < 100000; runTime++) {

    	numPlayer = (Random() % 3) + 2;
    	currentPlayer = Random() % numPlayer;

		memset(&G, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
        G.handCount[currentPlayer] = Random() % 7;
    	baronLocation = Random() % G.handCount[currentPlayer];
    	G.hand[p][baronLocation] = baron;
        int previousNumBuys = G.numBuys;
        int estateCount = G.supplyCount[estate];
        for (int otherCards = 0; otherCards <= handCount; otherCards++) {
        	if (otherCards != baronLocation) {
        		G.hand[currentPlayer][otherCards] = possibleCards[Random() % 16];
        	}
        }
        choiceOne = Random() % 2;
        baronCard(choiceOne, p, &G, baronLocation);

        //  Assertions
	                if (G.numBuys != previousNumBuys + 1) {  // Assert that buys were incremented
	                	printf("Buys are not correct!\n");
	                }

	                if (choiceOne == 0 && cardFinder(estate, p, &G, baronLocation) >= 0 && G.coins != currentCoins + 4) {  // Assert that coins added
	                	printf("Coins are not correct!\n");
	                }

	                if (choiceOne == 0 && cardFinder(estate, p, &G, baronLocation) >= 0) {  // Assert that the players hand gains an estate card
	                	printf("Estate was not added to hand!\n");
	                }

	                if (choiceOne == 0 && G.supplyCount[estate] != estateCount - 1) {  // Asserts the supply pile for estates is decremented
	                	printf("Estate supply Pile is not correct!\n");
	                }

	                if (choiceOne == 1 && cardFinder(estate, p, &G, baronLocation) != -1) {  // Assert that if trying to discard an estate it removes the estate from hand
	                	printf("Estate card not discarded from hand!\n");
	                }
	                if (choiceOne == 1 && G.supplyCount[estate] != estateCount) {  // Assert that if trying to discard an estate it removes the estate from hand
	                	printf("Gained an estate card when the player shouldnt have!\n");
	                }
	}
    printf("Tests Completed!\n");
    return 0;
}