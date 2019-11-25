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
    int numPlayer = 2;
    int maxBonus = 10;
    int p = 1;
    int r, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;


    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.handCount[p] = 5; // set the number of cards on hand
    G.discardCount[p] = 10;
    G.deckCount[p] = 15;
    //  Fill the entire hand with estate cards
    for (int estateCards = 0; estateCards <= G.handCount[p]; estateCards++) {
        G.hand[p][estateCards] = estate;
    }

    //  Fill the entire discard with estates
    for (int estateCards = 0; estateCards <= G.discardCount[p]; estateCards++) {
        G.discard[p][estateCards] = estate;
    }

    //  Fill the entire deck with estates
    for (int estateCards = 0; estateCards <= G.deckCount[p]; estateCards++) {
        G.deck[p][estateCards] = estate;
    }

    int expectedScore = G.deckCount[p] + G.discardCount[p] + G.handCount[p]
    int actualScore = scoreFor(p,&G);

    if (expectedScore != actualScore) {
        printf("The actual score is not correct.\n")
        printf("Expected score is %d.\n", expectedScore)
        printf("Actual score was %d.\n", actualScore)
    }
}
