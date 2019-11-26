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
               , remodel, gold, village, baron, great_hall};
    int testCards[3] = {great_hall, council_room, gold};
    struct gameState G;


    for (int eachCard = 0; eachCard < 3; eachCard++) {
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
        G.whoseTurn = p;
        G.handCount[p] = 5; // set the number of cards on hand
        G.discardCount[p] = 10;
        G.deckCount[p] = 15;

        for (int addCards = 0; addCards < G.handCount[p]; addCards++) {
            G.hand[p][addCards] = estate;
        }

        for (int addCards = 0; addCards < G.discardCount[p]; addCards++) {
            G.discard[p][addCards] = estate;
        }

        for (int addCards = 0; addCards < G.deckCount[p]; addCards++) {
            G.deck[p][addCards] = estate;
        }

        G.coins = 0;
        int currentCoins = G.coins;
        G.hand[p][0] = feast;

        printf("The last card in the discard is: %d\n", G.discard[p][10]);
        cardEffect(feast, testCards[eachCard], 0, 0, &G, 0, &maxBonus);
        printf("The last card in the discard is: %d\n", G.discard[p][10]);

        if (currentCoins != G.coins) {
            printf("The number of coins for the player is incorrect!\n");
        }

        if (G.discard[p][G.discardCount[p]] != testCards[eachCard] && testCards[eachCard] != gold) {
            printf("The player did not gain the card and it was a valid card choice.\n");
        }

        if (G.discard[p][G.discardCount[p]] != testCards[eachCard] && testCards[eachCard] == gold) {
            printf("The player gained a card when it was an invalid choice of card.\n");
        }
    }
}