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
    int minionLocation;
    int k[10] = {adventurer, gardens, mine, council_room, tribute
               , remodel, smithy, village, baron, great_hall};
    int makeDeck[9] = {gardens, gardens, copper, copper, baron
               , baron, gardens, copper, baron};
    struct gameState G;
    int nextPlayer;
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

    printf ("TESTING tributeCard():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (tributeLocation = 0; tributeLocation <= maxHandCount; tributeLocation++)
        {
        	for (handCount = 1; handCount <= maxHandCount; handCount++)
            {
            for (int nextPlayerDeck = 0; nextPlayerDeck <= 9; nextPlayerDeck++)
            	{
#if (NOISY_TEST == 1)
    printf("Test player %d with %d card(s). Tribute at pos %d.\n", p, handCount, tributeLocation);
#endif
	                memset(&G, 23, sizeof(struct gameState));   // clear the game state
	                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	                G.handCount[p] = handCount; // set the number of cards on hand
	                G.hand[p][tributeLocation] = tribute;
	                int currentCoins = G.coins;
	                int currentActions = 1;
	                int currentHand = handCount;
	                int discardStart = 9 - nextPlayerDeck;
	                if (p == 3) {
	                	nextPlayer = 0;
	                }
	                else {
	                	nextPlayer = p+1;
	                }

	                for (int otherCards = 0; otherCards <= handCount; otherCards++) {
	                	if (otherCards != tributeLocation) {
	                		G.hand[p][otherCards] = k[otherCards];
	                	}
	                }

	                G.discardCount[nextPlayer] = discardStart;
	                G.deckCount[nextPlayer] = nextPlayerDeck;

	                //  Adding cards to the discard of the next player
	                for (int nextPlayerDiscard = 0; nextPlayerDiscard < G.discardCount[nextPlayer]; nextPlayerDiscard++) {
		                G.discard[nextPlayer][nextPlayerDiscard] = makeDeck[nextPlayerDiscard];
	                }

	                for (int addPlayerDeck = 0; addPlayerDeck < nextPlayerDeck; addPlayerDeck++) {
	                	G.deck[nextPlayer][addPlayerDeck] = makeDeck[addPlayerDeck];
	                }

	                tributeCard(1, p, nextPlayer,  &G, tributeLocation);

	#if (NOISY_TEST == 1)
	                printf("Handsize is %d, Tribute is at pos %d.\n", handCount, tributeLocation);
	#endif
	                //  Assertions
                	if (G.discard[nextPlayer][G.discardCount[nextPlayer]] == G.discard[nextPlayer][G.discardCount[nextPlayer]-1]) {  // Assert that if both cards are of the same type that are revealed then the correct action is taken
                		if (G.discard[nextPlayer][G.discardCount[nextPlayer]] == gardens && G.handCount[p] != handCount + 1) {
                			printf("Handsize is incorrect for reveal of two victory cards!\n");
                		}

                		if (G.discard[nextPlayer][G.discardCount[nextPlayer]] == copper && G.coins != currentCoins + 2) {
                			printf("Coins is incorrect for reveal of two treasure cards!\n");
                		}

                		if (G.discard[nextPlayer][G.discardCount[nextPlayer]] == baron && currentActions != 2) {
                			printf("Actions is incorrect for reveal of two treasure cards!\n");
                		}
                	}

                	if (G.discardCount[nextPlayer] != discardStart + 2) {  //  Assert that if the deck had to be shuffled to complete the effect that it was actually shuffled.
                		int isSame = G.deckCount[nextPlayer];
                		for (int x = 0; x < G.deckCount[nextPlayer]; x++) {
                			if (makeDeck[x] != G.deck[nextPlayer][x]) {
                				isSame-= 1;
                			}
                		}
                		if (isSame == 0) {
                			printf("Deck was not shuffled when it should have been!\n");
                		}
                	}

	                // Deck size assert
	                if (nextPlayerDeck >= 2 && G.discardCount[nextPlayer] != discardStart + 2 ) {  // Assert that the player gains two coins if they choose that option
	                	printf("Cards were not discarded correctly!\n");
	                }
	            }
	        }
	    }
	}

    printf("Tests completed!\n");

    return 0;
}