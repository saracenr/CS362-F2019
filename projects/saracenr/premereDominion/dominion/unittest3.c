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
    int numPlayer = 4;
    int maxBonus = 10;
    int p, r, handCount;
    int ambassadorLocation;
    int k[10] = {adventurer, council_room, feast, gardens, ambassador
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

    printf ("TESTING ambassadorCard():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (ambassadorLocation = 0; ambassadorLocation <= maxHandCount; ambassadorLocation++)
        {
        	for (handCount = 1; handCount <= maxHandCount; handCount++)
            {
            for (int choice = -1; choice <= 3; choice++)
            	{
            		for (int revealedCard = 0; revealedCard <= handCount; revealedCard++) {
            			for (int amountOfRevealed = 0; amountOfRevealed <= handCount-1; amountOfRevealed++) {
		#if (NOISY_TEST == 1)
		    printf("Test player %d with %d card(s). Ambassador at pos %d.\n", p, handCount, ambassadorLocation);
		#endif
			                memset(&G, 23, sizeof(struct gameState));   // clear the game state
			                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
			                for (int eachPlayer = 0; eachPlayer < 4; eachPlayer++) {  // Sets number of cards for each player
			                	G.handCount[eachPlayer] = handCount;
			                }
			                G.hand[p][ambassadorLocation] = ambassador;
			                for (int otherCards = 0; otherCards <= handCount; otherCards++) {
			                	if (otherCards != ambassadorLocation) {
			                		G.hand[p][otherCards] = k[otherCards];
			                	}
			                }

			                for (int copies = 0; copies < amountOfRevealed; copies++) {
			                	gainCard(G.hand[p][revealedCard], &G, 2, p);
			                }

			                for (int eachPlayer = 0; eachPlayer < 4; eachPlayer++) {  // Sets number of cards for each player
			                	if (p != eachPlayer) {
			                		for (int otherCards = 0; otherCards <= handCount; otherCards++) {
			                		G.hand[eachPlayer][otherCards] = k[otherCards];
			                		}
			                	}
			                }

			                int successful = ambassadorCard(revealedCard,choice, p, &G, ambassadorLocation);
		#if (NOISY_TEST == 1)
			printf("Handsize is %d, Ambassador is at pos %d. They chose to reveal %d card copies.\n", handCount, ambassadorLocation, choice);
		#endif

			                //  Assertions
			                if ((choice > 2 || choice < 0)  && successful != -1) {  //  Assert the function returns -1 if the choice is invalid
			                	printf("Choice was invalid but the card function was successful!\n");
			                }

			                if (choice == 0 && G.handCount[p] != handCount-1 && successful != -1) {  // Assert that the ambassador card was discarded and no cards gained
			                	printf("Hand for current player is not correct for successful returning 0 cards!\n");
			                }
			                else if (choice == 1 && G.handCount[p] != handCount-2 && successful != -1) {   // Assert that the ambassador card was discarded and no cards gained
			                	printf("Hand for current player is not correct for successful returning 1 cards!\n");
			                }
			                else if (choice == 2 && G.handCount[p] != handCount-3 && successful != -1) {   // Assert that the ambassador card was discarded and no cards gained
			                	printf("Hand for current player is not correct for successful returning 2 cards!\n");
			                }

			                // Assert that cannot reveal ambassador card played to its own effect
			                if (handCount == ambassadorLocation && successful != -1) { 
			                	printf("Player revealed the played ambassador card for its effect, this is incorrect!\n");
			                }

			                //  Asserts each opponent gained the correct amount of cards.
			                for (int eachPlayer = 0; eachPlayer < 4; eachPlayer++) {  // Checks each players hand
			                	if (p != eachPlayer) {
					                if (choice == 0 && G.handCount[eachPlayer] != handCount && successful != -1) {  //  Assert that the number of cards gained for each player is correct
					                	printf("Hand for opponent player is not correct for successful returning 0 cards!\n");
					                }
					                else if (choice == 1 && G.handCount[p] != handCount+1 && successful != -1) {   //  Assert that the number of cards gained for each player is correct
					                	printf("Hand for opponent player is not correct for successful returning 1 cards!\n");
					                }
					                else if (choice == 2 && G.handCount[p] != handCount+2 && successful != -1) {   //  Assert that the number of cards gained for each player is correct
					                	printf("Hand for opponent player is not correct for successful returning 2 cards!\n");
					                }
					            }
				            }
				        }
			        }
	            }
	        }
	    }
	}

    printf("Tests completed!\n");

    return 0;
}