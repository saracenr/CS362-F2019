#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <stdlib.h>

int main() {
    int i;
    int seed = 1000;
    PlantSeeds(100);
    int numPlayer;
    int currentPlayer, nextPlayer;
    int maxBonus = 10;
    int r, handCount, runTime, choiceOne, choiceTwo;
    int tributeLocation;
    int currentCoins, currentActions;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, tribute, great_hall};
    int possibleCards[16] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, tribute, great_hall, copper, silver, gold, estate, duchy, province};
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

    // for (runTime = 0; runTime < 100000; runTime++) {
    for (runTime = 0; runTime < 1000000; runTime++) {
    	SelectStream(2);
        double rand_value = Random();
        double rand_3 = rand_value * 3;
        // double rand_1000 = rand_value * 1000;
        double floored = floor(rand_3);
        int cast = (int) floored;
        numPlayer = cast + 2;
    	// printf("Rand value: %f.\nTimes 3: %f.\nFloored: %f\nCast: %d\n", rand_value, rand_3, floored, cast);


    	// numPlayer = (int)floor(Random() * 3) + 2;
    	currentPlayer = (int)floor(Random() * numPlayer);
    	// printf("Num player: %d. Current player: %d.\n", numPlayer, currentPlayer);

		memset(&G, 23, sizeof(struct gameState)); // clear the game state
        r = initializeGame(numPlayer, k, -1, &G); // initialize a new game
        handCount = (int)floor(Random() * 7);
        int nextPlayerDeck = (int)floor(Random() * 10);
        int discardStart = 10 - nextPlayerDeck;
        G.handCount[currentPlayer] = handCount;
    	tributeLocation = (int)floor(Random() * G.handCount[currentPlayer]);
    	G.hand[currentPlayer][tributeLocation] = tribute;
        currentActions = 1;
    	currentCoins = G.coins;
        for (int otherCards = 0; otherCards <= G.handCount[currentPlayer]; otherCards++) {
        	if (otherCards != tributeLocation) {
        		G.hand[currentPlayer][otherCards] = possibleCards[(int)floor(Random() * 15)];
        	}
        }

        if (currentPlayer == 3) {
            nextPlayer = 0;
        }
        else {
            nextPlayer = currentPlayer+1;
        }

        G.discardCount[nextPlayer] = discardStart;
        G.deckCount[nextPlayer] = nextPlayerDeck;
        int checkCards[10];
        int checkCardsSize = 0;
        int addedCard;

        //  Adding cards to the discard of the next player
        for (int nextPlayerDiscard = 0; nextPlayerDiscard < G.discardCount[nextPlayer]; nextPlayerDiscard++) {
            addedCard = possibleCards[(int)floor(Random() * 15)];
            G.discard[nextPlayer][nextPlayerDiscard] = addedCard;
            checkCards[checkCardsSize] = addedCard;
            checkCardsSize++;
        }

        //  Adding cards to the deck of the next player
        for (int addPlayerDeck = 0; addPlayerDeck < nextPlayerDeck; addPlayerDeck++) {
            addedCard = possibleCards[(int)floor(Random() * 15)];
            G.deck[nextPlayer][addPlayerDeck] = addedCard;
            checkCards[checkCardsSize] = addedCard;
            checkCardsSize++;
        }

        int* revealedCards = NULL;
        cardTribute(currentPlayer, nextPlayer, &G, revealedCards);

        printf("Current player is %d.  Tribute is at location %d.\n", currentPlayer, tributeLocation);

        //  Assertions
        if (G.discard[nextPlayer][G.discardCount[nextPlayer]] == G.discard[nextPlayer][G.discardCount[nextPlayer]-1]) {  // Assert that if both cards are of the same type that are revealed then the correct action is taken
            if (((estate <= G.discard[nextPlayer][G.discardCount[nextPlayer]]
                 && G.discard[nextPlayer][G.discardCount[nextPlayer]] <= province)
                 || G.discard[nextPlayer][G.discardCount[nextPlayer]] == gardens)
                 && G.handCount[currentPlayer] != handCount + 1 ) {
                printf("Handsize is incorrect for reveal of two victory cards!\n");
            }

            if (copper <= G.discard[nextPlayer][G.discardCount[nextPlayer]]
                && G.discard[nextPlayer][G.discardCount[nextPlayer]] <= gold 
                && G.coins != currentCoins + 2) {
                printf("Coins is incorrect for reveal of two treasure cards!\n");
            }

            if (adventurer <= G.discard[nextPlayer][G.discardCount[nextPlayer]]
                 && G.discard[nextPlayer][G.discardCount[nextPlayer]] <= treasure_map
                 && G.discard[nextPlayer][G.discardCount[nextPlayer]] != gardens
                 && currentActions != 2) {
                printf("Actions is incorrect for reveal of two treasure cards!\n");
            }
        }

        if (G.discard[nextPlayer][G.discardCount[nextPlayer]] != G.discard[nextPlayer][G.discardCount[nextPlayer]-1]) {  // Assert that if both cards are not the same type that are revealed then the correct action is taken
            if (((estate <= G.discard[nextPlayer][G.discardCount[nextPlayer]]
                 && G.discard[nextPlayer][G.discardCount[nextPlayer]] <= province)
                 || G.discard[nextPlayer][G.discardCount[nextPlayer]] == gardens)
                 && G.handCount[currentPlayer] != handCount + 1 ) {
                printf("Handsize is incorrect for reveal of one victory cards!\n");
            }

            if (copper <= G.discard[nextPlayer][G.discardCount[nextPlayer]]
                && G.discard[nextPlayer][G.discardCount[nextPlayer]] <= gold 
                && G.coins != currentCoins + 2) {
                printf("Coins is incorrect for reveal of one treasure cards!\n");
            }

            if (adventurer <= G.discard[nextPlayer][G.discardCount[nextPlayer]]
                 && G.discard[nextPlayer][G.discardCount[nextPlayer]] <= treasure_map
                 && G.discard[nextPlayer][G.discardCount[nextPlayer]] != gardens
                 && currentActions != 2) {
                printf("Actions is incorrect for reveal of one treasure cards!\n");
            }
        }

        if (G.discardCount[nextPlayer] != discardStart + 2) {  //  Assert that if the deck had to be shuffled to complete the effect that it was actually shuffled.
            int isSame = G.deckCount[nextPlayer];
            for (int x = 0; x < G.deckCount[nextPlayer]; x++) {
                if (checkCards[x] != G.deck[nextPlayer][x]) {
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
    printf("Tests Completed!\n");
    return 0;
}