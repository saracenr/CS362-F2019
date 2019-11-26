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
    int k[10] = {adventurer, council_room, feast, feast, mine
               , remodel, smithy, village, baron, great_hall};
    int testCards[3] = {great_hall, council_room, gold};
    struct gameState G;


    for (int eachCard = 0; eachCard < 3; eachCard++) {
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
        G.handCount[p] = 5; // set the number of cards on hand
        G.coins = 0;
        int currentCoins = G.coins;
        G.hand[p][0] = feast;


        cardEffect(feast, testCards[eachCard], 0, 0, &G, 0, maxBonus);

        if (currentCoins != G.coins) {
            printf("The number of coins for the player is incorrect!\n");
        }

        if (G.hand[p][5] != testCards[eachCard] && testCards[eachCard] != gold) {
            printf("The player did not gain the card and it was a valid card choice.\n");
        }

        if (G.hand[p][5] != testCards[eachCard] && testCards[eachCard] == gold) {
            printf("The player gained a card when it was an invalid choice of card.\n");
        }


    }