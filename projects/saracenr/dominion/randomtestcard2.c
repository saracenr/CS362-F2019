#include "dominion.h"
#include "dominion_helpers.h"
#include "cardFunctions.h"
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
    int currentPlayer;
    int maxBonus = 10;
    int r, handCount, runTime, choiceOne, choiceTwo;
    int minionLocation;
    int currentCoins, currentActions;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, minion, great_hall};
    int possibleCards[16] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, minion, great_hall, copper, silver, gold, estate, duchy, province};
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
    for (runTime = 0; runTime < 100000; runTime++) {
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
        G.handCount[currentPlayer] = handCount;
    	minionLocation = (int)floor(Random() * G.handCount[currentPlayer]);
    	G.hand[currentPlayer][minionLocation] = baron;
        currentActions = 1;
    	currentCoins = G.coins;
        for (int otherCards = 0; otherCards <= G.handCount[currentPlayer]; otherCards++) {
        	if (otherCards != minionLocation) {
        		G.hand[currentPlayer][otherCards] = possibleCards[(int)floor(Random() * 15)];
        	}
        }

        for (int player = 0; player < numPlayer; player++) {
            if (player != currentPlayer) {
                G.handCount[player] = 5;
                for (int otherCards = 0; otherCards <= G.handCount[player]; otherCards++) {
                    G.hand[player][otherCards] = possibleCards[(int)floor(Random() * 15)];
                }
            }
        }

        choiceOne = (int)floor(Random() * 2);
        if (choiceOne == 1) {
            choiceTwo = 0;
        }
        else {
            choiceTwo = 1;
        }

        minionCard(choiceOne, choiceTwo, currentPlayer, &G, minionLocation);

        printf("Current player is %d.  Baron is at location %d.  ChoiceOne is %d.\n", currentPlayer, minionLocation, choiceOne);

        //  Assertions
        if (G.numActions != 1) {  // Assert that actions were incremented no matter what
            printf("Actions are not correct!\n");
        }

        // Coin Assert
        if (choiceOne == 1 && G.coins != currentCoins + 2) {  // Assert that the player gains two coins if they choose that option
            printf("Coins were not gained!\n");
        }
        else if (choiceOne == 0 && G.coins != currentCoins) {  //  Assert that the player didnt gain two coins if they didnt choose to
            printf("Coin count is not correct, no change should have happened!\n");
        }

        // Hand Assert
        if (choiceTwo == 0 && G.handCount[currentPlayer] != handCount - 1) {  // Asserts that the players hand count is correct
            printf("Hand count is not correct after choosing choice 1!\n");
        }
        else if (choiceTwo == 1 && G.handCount[currentPlayer] != handCount + 3) {  // Asserts that the players hand count is correct
            printf("Hand count is not correct after choosing choice 2!\n");
        }

        //  Opponent hand assert
        if (choiceTwo == 0 && currentPlayer < 3 && G.handCount[currentPlayer+1] != 5) {  // Assert that opponent is not forced to discard
            printf("Hand count is not correct for opponent after choosing choice 1!\n");
        }
        else if (choiceTwo == 1 && currentPlayer < 3 && G.handCount[currentPlayer+1] != 4) {  // Assert that opponent is forced to discard
            printf("Hand count is not correct for opponent after choosing choice 2!\n");
        }

        if (G.discard[currentPlayer][G.discardCount[currentPlayer]] != minion) {  //  Asserts that the minion card was discarded and not trashed.
            printf("Minion card was not discarded after being played!\n");
        }
    }
    printf("Tests Completed!\n");
    return 0;
}