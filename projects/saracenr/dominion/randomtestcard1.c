#include "dominion.h"
#include "dominion_helpers.h"
#include "cardFunctions.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <stdlib.h>

int main() {
    int i;
    int seed = 1000;
    PlantSeeds(seed);
    int numPlayer;
    int currentPlayer;
    int maxBonus = 10;
    int r, handCount, runTime, choiceOne;
    int estateLocation;
    int baronLocation;
    int currentCoins;
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

    for (runTime = 0; runTime < 1000000; runTime++) {

    	numPlayer = (int)floor(Random() * 3) + 2;
    	currentPlayer = (int)floor(Random() * numPlayer);

		memset(&G, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
        G.handCount[currentPlayer] = (int)floor(Random() * 7);
    	baronLocation = (int)floor(Random() * G.handCount[currentPlayer]);
    	G.hand[currentPlayer][baronLocation] = baron;
    	currentCoins = G.coins;
        int previousNumBuys = G.numBuys;
        int estateCount = G.supplyCount[estate];
        for (int otherCards = 0; otherCards <= G.handCount[currentPlayer]; otherCards++) {
        	if (otherCards != baronLocation) {
        		G.hand[currentPlayer][otherCards] = possibleCards[(int)floor(Random() * 15)];
        	}
        }
        choiceOne = (int)floor(Random() * 2);
        baronCard(choiceOne, currentPlayer, &G, baronLocation);

        printf("Current player is %d.  Baron is at location %d.  ChoiceOne is %d.\n", currentPlayer, baronLocation, choiceOne);

        //  Assertions
        if (G.numBuys != previousNumBuys + 1) {  // Assert that buys were incremented
        	printf("Buys are not correct!\n");
        }

        if (choiceOne == 0 && cardFinder(estate, currentPlayer, &G, baronLocation) >= 0 && G.coins != currentCoins + 4) {  // Assert that coins added
        	printf("Coins are not correct!\n");
        }

        if (choiceOne == 0 && cardFinder(estate, currentPlayer, &G, baronLocation) >= 0) {  // Assert that the players hand gains an estate card
        	printf("Estate was not added to hand!\n");
        }

        if (choiceOne == 0 && G.supplyCount[estate] != estateCount - 1) {  // Asserts the supply pile for estates is decremented
        	printf("Estate supply Pile is not correct!\n");
        }

        if (choiceOne == 1 && cardFinder(estate, currentPlayer, &G, baronLocation) != -1) {  // Assert that if trying to discard an estate it removes the estate from hand
        	printf("Estate card not discarded from hand!\n");
        }
        if (choiceOne == 1 && G.supplyCount[estate] != estateCount) {  // Assert that if trying to discard an estate it removes the estate from hand
        	printf("Gained an estate card when the player shouldnt have!\n");
        }
	}
    printf("Tests Completed!\n");
    return 0;
}