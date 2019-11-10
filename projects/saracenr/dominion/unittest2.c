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

    printf ("TESTING minionCard():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (minionLocation = 0; minionLocation <= maxHandCount; minionLocation++)
        {
        	for (handCount = 1; handCount <= maxHandCount; handCount++)
            {
            for (int choice = 0; choice <= 1; choice++)
            	{
#if (NOISY_TEST == 1)
    printf("Test player %d with %d card(s). Minion at pos %d.\n", p, handCount, minionLocation);
#endif
	                memset(&G, 23, sizeof(struct gameState));   // clear the game state
	                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	                G.handCount[p] = handCount; // set the number of cards on hand
	                G.hand[p][minionLocation] = minion;
	                int currentCoins = G.coins;
	                int currentActions = 1;
	                if (p == 0) {
	                	G.handCount[1] = 5;
	                }
	                else {
	                	G.handCount[0] = 5;
	                }
	                for (int otherCards = 0; otherCards <= handCount; otherCards++) {
	                	if (otherCards != minionLocation) {
	                		G.hand[p][otherCards] = k[otherCards];
	                	}
	                }
	                if (choice == 0) {
	                	minionCard(1, 0, p, &G, minionLocation);
	                }
	                else {
	                	minionCard(0, 1, p, &G, minionLocation);
	                }

	#if (NOISY_TEST == 1)
	                printf("Handsize is %d, Minion is at pos %d. They chose choice %d\n.", handCount, minionLocation, choice+1);
	#endif
	                //  Assertions
	                if (G.numActions != 1) {  // Assert that actions were incremented no matter what
	                	printf("Actions are not correct!\n");
	                }

	                // Coin Assert
	                if (choiceOne == 0 && G.coins != currentCoins + 2) {  // Assert that the player gains two coins if they choose that option
	                	printf("Coins were not gained!\n");
	                }
	                else if (choiceOne == 1 && G.coins != currentCoins) {  //  Assert that the player didnt gain two coins if they didnt choose to
	                	printf("Coin count is not correct, no change should have happened!\n");
	                }

	                // Hand Assert
	                if (choiceOne == 0 && G.handCount[p] != handCount - 1) {  // Asserts that the players hand count is correct
	                	printf("Hand count is not correct after choosing choice 1!\n");
	                }
	                else if (choiceOne == 1 && G.handCount[p] != 4) {  // Asserts that the players hand count is correct
	                	printf("Hand count is not correct after choosing choice 2!\n");
	                }

	                //  Opponent hand assert
	                if (choiceOne == 0 && p == 0 && G.handCount[p+1] != 5) {  // Assert that opponent is not forced to discard
	                	printf("Hand count is not correct for opponent after choosing choice 1!\n");
	                }
	                else if (choiceOne == 1 && p == 0 && G.handCount[p+1] != 4) {  // Assert that opponent is forced to discard
	                	printf("Hand count is not correct for opponent after choosing choice 2!\n");
	                }
	            }
	        }
	    }
	}

    printf("Tests completed!\n");

    return 0;
}