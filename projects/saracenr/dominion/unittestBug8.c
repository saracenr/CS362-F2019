#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p = 0;
    int r, handCount;
    int k[10] = {adventurer, council_room, feast, feast, mine
               , remodel, minion, village, baron, great_hall};
    struct gameState G;


    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.whoseTurn = p;
    G.handCount[p] = 5; // set the number of cards on hand
    // Add cards to hand
    for (int addCards = 0; addCards < G.deckCount[p]; addCards++) {
        G.deck[p][addCards] = estate;
    }
    G.coins = 0;
    int currentCoins = G.coins;
    G.hand[p][0] = minion;

    playCard(minion, 1, 0, 0, &G);

    if (currentCoins + 2  != G.coins) {
        printf("The number of coins for the player is incorrect!\n");
    }

    if (maxBonus != 2) {
        printf("Bonus was not correctly updated!.\n");
    }
}