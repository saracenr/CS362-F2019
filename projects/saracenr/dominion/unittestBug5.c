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
    int p = 1;
    int r, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;


    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.handCount[p] = 6; // set the number of cards on hand
    G.discardCount[p] = 10;
    G.deckCount[p] = 15;
    //  Fill the entire hand with VP cards: 1 Curse,1 estate, 1 Duchy, 1 Province, 1 Greathall, 1 Garden
    for (int vpCards = 0; vpCards < G.handCount[p]; vpCards++) {
        if (vpCards == 4) {
            G.hand[p][vpCards] = gardens;
        }
        else if (vpCards == 5) {
            G.hand[p][vpCards] = great_hall;
        }
        else {
           G.hand[p][vpCards] = vpCards; 
        }
    }

    //  Fill the entire hand with VP cards: 2 Curse, 2 estate, 2 Duchy, 2 Province, 1 Greathall, 1 Garden
    for (int vpCards = 0; vpCards < G.discardCount[p]; vpCards++) {
        if (vpCards == 4) {
            G.discard[p][vpCards] = gardens;
        }
        else if (vpCards == 5) {
            G.discard[p][vpCards] = great_hall;
        }
        else {
           G.discard[p][vpCards] = vpCards % 4; 
        }
    }

    //  Fill the entire hand with VP cards: 3 Curse,3 estate, 3 Duchy, 4 Province, 1 Greathall, 1 Garden
    for (int vpCards = 0; vpCards < G.deckCount[p]; vpCards++) {
        if (vpCards == 4) {
            G.deck[p][vpCards] = gardens;
        }
        else if (vpCards == 5) {
            G.deck[p][vpCards] = great_hall;
        }
        else {
           G.deck[p][vpCards] = vpCards % 4; 
        }
    }

    int expectedScore = -5 + 5 + 18 + 30 + 3 + 9; // Curses + estates + Duchys + Prov + great_hall + garden SHOULD BE 60
    int actualScore = scoreFor(p,&G);

    if (expectedScore != actualScore) {
        printf("The actual score is not correct.\n");
        printf("Expected score is %d.\n", expectedScore);
        printf("Actual score was %d.\n", actualScore);
    }
}
