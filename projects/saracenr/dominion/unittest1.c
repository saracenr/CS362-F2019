#include "dominion.h"
#include "dominion_helpers.h"
#include "cardFunctions.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int estateLocation;
    int baronLocation;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
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

    printf ("TESTING baronCard():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (baronLocation = 0; baronLocation <= maxHandCount; baronLocation++)
        {
        	for (handCount = 1; handCount <= maxHandCount; handCount++)
            {
            for (int choiceOne = 0; choiceOne <= 1; choiceOne++)
            	{
#if (NOISY_TEST == 1)
    printf("Test player %d with %d cards baron at pos %d.\n", p, handCount, baronLocation);
#endif
	                memset(&G, 23, sizeof(struct gameState));   // clear the game state
	                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	                G.handCount[p] = handCount; // set the number of cards on hand
	                G.hand[p][baronLocation] = baron;
	                int previousNumBuys = G.numBuys;
	                int estateCount = G.supplyCount[estate];
	                for (int otherCards = 0; otherCards <= handCount; otherCards++) {
	                	if (otherCards != baronLocation) {
	                		G.hand[p][otherCards] = k[otherCards];
	                	}
	                }
	                baronCard(choiceOne, p, &G, baronLocation);
	#if (NOISY_TEST == 1)
	                printf("Handsize is %d, baron is at pos %d. No Estate in hand, trying %d. \n", handCount, baronLocation, choiceOne);
	#endif
	                //  Assertions
	                if (G.numBuys =! previousNumBuys + 1) {  // Assert that buys were incremented
	                	printf("Buys are not correct!\n");
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

	                // Adds estates to hand
	                if (handCount > 2) {
	                	for (estateLocation = 0; estateLocation <= handCount; estateLocation++) {
	                		if (estateLocation != baronLocation) {
#if (NOISY_TEST == 1)
	printf("Handsize is %d, baron is at pos %d. Estate in hand at pos %d \n", handCount, baronLocation, estateLocation);
#endif
				                memset(&G, 23, sizeof(struct gameState));   // clear the game state
				                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
				                G.handCount[p] = handCount; // set the number of cards on hand
				                G.hand[p][baronLocation] = baron;
				                G.hand[p][estateLocation] = estate;
				                int previousNumBuys = G.numBuys;
				                int estateCount = G.supplyCount[estate];
				                for (int otherCards = 0; otherCards <= handCount; otherCards++) {
				                	if (otherCards != baronLocation && otherCards != baronLocation) {
				                		G.hand[p][otherCards] = k[otherCards];
				                	}
				                }
				                baronCard(choiceOne, p, &G, baronLocation);

							                //  Assertions
				                if (G.numBuys =! previousNumBuys + 1) {  // Assert that buys were incremented
				                	printf("Buys are not correct!\n");
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
		               }
		           }
	            }
	        }
	    }
	}

    printf("All tests passed!\n");

    return 0;
}