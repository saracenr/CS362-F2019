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
    int nextPlayer = 1;
    int r; 
    int handCount = 5;
    int k[10] = {adventurer, council_room, feast, feast, mine
               , remodel, gold, village, baron, great_hall};
    int testCards[3] = {great_hall, council_room, gold};
    struct gameState G;

    //  Iterate using varying deck sizes from 0 to 4
    for (int deckSize = 0; deckSize < 5; deckSize++)
    {
        //  Iterate using varying discard sizes from 0 to 4
        for (int discardSize = 2; discardSize < 5; discardSize++)
        {
            //  Creating a case when we will reveal two of the same card
            for (int duplicateReveal = 0; duplicateReveal < 2; duplicateReveal++)
            {
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount; // set the number of cards on hand
                G.discardCount[nextPlayer] = discardSize;
                G.deckCount[nextPlayer] = deckSize;  
                G.deckCount[p] = 10;
                G.whoseTurn = p;
                // Add estate cards to hand
                for (int addCards = 0; addCards < G.handCount[p]; addCards++) {
                        G.hand[p][addCards] = estate;
                }

                // Add the tribute card to the hand.
                G.hand[p][0] = tribute;

                // Fills the next players discard and deck with either different cards or the same cards
                for (int addCards = 0; addCards < G.discardCount[nextPlayer]; addCards++) {
                    if (duplicateReveal == 1) {
                        G.discard[nextPlayer][addCards] = testCards[discardSize % 3];
                    }
                    else {
                        G.discard[nextPlayer][addCards] = testCards[addCards % 3];
                    }
                }

                for (int addCards = 0; addCards < G.deckCount[nextPlayer]; addCards++) {
                    if (duplicateReveal == 1) {
                        G.deck[nextPlayer][addCards] = testCards[discardSize % 3];
                    }
                    else {
                        G.deck[nextPlayer][addCards] = testCards[addCards % 3];
                    }
                }
                //  Fill the current players deck.
                for (int addCards = 0; addCards < G.deckCount[p]; addCards++) {
                    G.deck[p][addCards] = estate;
                }

                // Initialize variables to track the current players resources to check them using asserts.
                int currentCoins = G.coins;
                int currentActions = 1;
                int currentHand = handCount;
                int revealedCards[2] = {-1, -1};
                int noCardsRevealed = 0;

                if ((G.discardCount[nextPlayer] + G.deckCount[nextPlayer]) <= 1) {
                    if (G.deckCount[nextPlayer] > 0) {
                        revealedCards[0] = G.deck[nextPlayer][G.deckCount[nextPlayer]-1];
                    }
                    else if (G.discardCount[nextPlayer] > 0) {
                        revealedCards[0] = G.discard[nextPlayer][G.discardCount[nextPlayer]-1];
                    }
                    else {
                        noCardsRevealed = 1;
                    }
                }
                else {
                    if (G.deckCount[nextPlayer] == 0) {
                        for (i = 0; i < G.discardCount[nextPlayer]; i++) {
                            G.deck[nextPlayer][i] = G.discard[nextPlayer][i];//Move to deck
                            G.deckCount[nextPlayer]++;
                            G.discard[nextPlayer][i] = -1;
                            G.discardCount[nextPlayer]--;
                        }
                    }
                    revealedCards[0] = G.deck[nextPlayer][G.deckCount[nextPlayer]-1];
                    revealedCards[1] = G.deck[nextPlayer][G.deckCount[nextPlayer]-2];
                }

                printf("deckSize: %d, discardSize: %d, dups: %d.\n", deckSize, discardSize, duplicateReveal);
                cardEffect(tribute, 0, 0, 0, &G, 0, &maxBonus);
                printf("I made it to past the function!\n");

                if (noCardsRevealed == 1) {
                    printf("Player had no deck or discard to reveal!\n");
                    if (currentCoins != G.coins) {
                        printf("No cards revealed but coins were changed.\n");
                    }
                    if (G.numActions != 0) {
                        printf("Actions were incorrectly changed but no cards were revealed.\n");
                    }
                    if (currentHand - 1 != G.handCount[p]) {
                        printf("Player hand size is wrong but not cards were revealed.\n");
                    }
                }
                else {
                    if (revealedCards[0] == revealedCards[1]) {  // Assert that if both cards are of the same type that are revealed then the correct action is taken
                        if (revealedCards[0] == great_hall && G.handCount[p] != handCount + 1) {
                            printf("Handsize is incorrect for reveal of two victory cards!\n");
                        }

                        if (revealedCards[0] == gold && G.coins != currentCoins + 2) {
                            printf("Coins is incorrect for reveal of two treasure cards!\n");
                        }

                        if (revealedCards[0] == council_room && G.numActions != 2) {
                            printf("Actions is incorrect for reveal of two treasure cards!\n");
                        }
                    }

                    if (revealedCards[0] != revealedCards[1]) {  // Assert that if both cards are not the same type that are revealed then the correct action is taken
                        if (revealedCards[0] == great_hall && G.handCount[p] != handCount + 1) {
                            printf("Handsize is incorrect for reveal of a victory card!\n");
                        }

                        if (revealedCards[0] == gold && G.coins != currentCoins + 2) {
                            printf("Coins is incorrect for reveal of a treasure card!\n");
                        }

                        if (revealedCards[0] == council_room && G.numActions != 2) {
                            printf("Actions is incorrect for reveal of a treasure card!\n");
                        }

                        if (revealedCards[1] == great_hall && G.handCount[p] != handCount + 1) {
                            printf("Handsize is incorrect for reveal of a victory card!\n");
                        }

                        if (revealedCards[1] == gold && G.coins != currentCoins + 2) {
                            printf("Coins is incorrect for reveal of a treasure card!\n");
                        }

                        if (revealedCards[1] == council_room && G.numActions != 2) {
                            printf("Actions is incorrect for reveal of a treasure card!\n");
                        }
                    }

                    // Deck size assert
                    if (deckSize >= 2 && G.discardCount[nextPlayer] != discardSize + 2 ) {  // Assert that the player gains two coins if they choose that option
                        printf("Cards were not discarded correctly!\n");
                    }
                }
            }
        }
    }
}