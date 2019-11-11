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
    int treasureLocation;
    int mineLocation;
    int treasures[3] = {copper,silver,gold};
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

    printf ("TESTING mineCard():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (mineLocation = 0; mineLocation <= maxHandCount; mineLocation++)
        {
        	for (handCount = 1; handCount <= maxHandCount; handCount++)
            {
            for (int choiceOne = 0; choiceOne <= 2; choiceOne++)
            	{
#if (NOISY_TEST == 1)
    printf("Test player %d with %d card(s). Mine at pos %d.\n", p, handCount, mineLocation);
#endif
	                memset(&G, 23, sizeof(struct gameState));   // clear the game state
	                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	                G.handCount[p] = handCount; // set the number of cards on hand
	                G.hand[p][mineLocation] = mine;
	                int currentCoins = G.coins;
	                int currentActions = 1;
	                for (int otherCards = 0; otherCards <= handCount; otherCards++) {
	                	if (otherCards != mineLocation) {
	                		G.hand[p][otherCards] = k[otherCards];
	                	}
	                }
	                mineCard(choiceOne,treasures[choiceOne], p, &G, mineLocation);
	#if (NOISY_TEST == 1)
	                printf("Handsize is %d, Mine is at pos %d. No treasure in hand.\n", handCount, mineLocation);
	#endif
	                //  Assertions
	                if (cardFinder(treasures[choiceOne], p, &G, mineLocation) !=  -1) {  // Assert that does not gain a copy of the chosen card
	                	printf("Desired treasure was added to hand when it should not have been!\n");
	                }

	                if (G.handCount[p] != handCount - 1) {  // Asserts the mine card was removed from hand after being played
	                	printf("Hand size is not correct after playing mine!\n");
	                }

	                if (G.numActions != 0) {  // Assert that actions are decremented
	                	printf("Actions were not decremented!\n");
	                }

	                // Adds treasures to hand
	                if (handCount > 2) {
	                	for (treasureLocation = 0; treasureLocation <= handCount; treasureLocation++) {
	                		for (int treasureChoice = 0 ; treasureChoice < 3; treasureChoice++) {
		                		if (treasureLocation != mineLocation) {
	#if (NOISY_TEST == 1)
		printf("Handsize is %d, Mine is at pos %d. Treasure in hand at pos %d. \n", handCount, mineLocation, treasureLocation);
	#endif
					                memset(&G, 23, sizeof(struct gameState));   // clear the game state
					                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
					                G.handCount[p] = handCount; // set the number of cards on hand
					                G.hand[p][mineLocation] = mine;
					                G.hand[p][treasureLocation] = treasures[choiceOne];
					                int currentCoins = G.coins;
					                for (int otherCards = 0; otherCards <= handCount; otherCards++) {
					                	if (otherCards != mineLocation && otherCards != treasureLocation) {
					                		G.hand[p][otherCards] = k[otherCards];
					                	}
					                }
					                mineCard(treasureLocation, treasure[treasureChoice], p, &G, mineLocation);

									//  Assertions
					                if (G.hand[p][treasureLocation] + 3 >= treasure[treasureChoice] && cardFinder(treasures[choiceOne], p, &G, mineLocation) !=  >= 0) {  // Assert that does gain a copy of the chosen card
					                	printf("Desired treasure was not added to hand when it should have been!\n");
					                }
					                else if (G.hand[p][treasureLocation] + 3 < treasure[treasureChoice] && cardFinder(treasures[choiceOne], p, &G, mineLocation) != -1) {  // Assert that does not gain a copy of the chosen card
					                	printf("Desired treasure was added to hand when it should not have been!\n");
					                }

					                if (G.handCount[p] != handCount - 1) {  // Asserts the mine card was removed from hand after being played
					                	printf("Hand size is not correct after playing mine!\n");
					                }

					                if (G.numActions != 0) {  // Assert that actions are decremented
					                	printf("Actions were not decremented!\n");
					                }
			            		}
			            	}
		               }
		           }
	            }
	        }
	    }
	}

    printf("Tests Completed!\n");

    return 0;
}