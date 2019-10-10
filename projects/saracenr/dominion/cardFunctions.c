#include "cardFunctions.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// cardToFind is the card you wish to find the position for in the current players hand
// currentCardHandPos is the current card that is being played's hand positions (handPos in cardEffect)
// currentCardHandPos exists incase the card we are trying to find is the same name as card being played.
int cardFinder(int cardToFind, int player, struct gameState *state, int currentCardHandPos) {
	// Iterates over the hand to try to find the cardToFind
	for (int p = 0; p <= state->handCount[player]; p++) {
		//  If card is found it returns its index position p
		if (state->hand[player][p] == cardToFind && p != currentCardHandPos) {
			return p;
		}
	}
	//  returns -1 if card is not found in current players hand
	return -1;
}

//  This helper functino discards the hand of the specified player
void discardHand(int player, struct gameState *state) {
    while(state->handCount[player] > 0) {
        discardCard(0, player, state, 0);
    }
}

//  This helper function draws a specified number of cards for the specified player
void drawMultCards(int player, int numberOfCards, struct gameState *state) {
    for (i = 0; i < numberOfCards; i++)
        {
            drawCard(player, state);
        }
}

int isTreasure(int card) {
    if (card < copper || card > gold)
    {
        return 0;
    }
    else {
        return card;
    }
}

int isVictory(int card) {
    if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall) {
        return 1;
    }
    else {
        return 0
    }
}

int baronCard(int choice1, int currentPlayer, struct gameState *state, int handPos) {
	state->numBuys++;
	if (choice1 > 0) { //Boolean true or going to discard an estate
		// Finds the first estate card in the players hand returns -1 if does not exist
		int estateToDiscard = cardFinder(estate, currentPlayer, state, handPos);
		//  If there is no estate card in the current players hand
        if (estateToDiscard == -1) {
        	if(DEBUG) {
                    printf("No estate cards in your hand, invalid choice\n");
                    printf("Must gain an estate if there are any\n");
                }
                // Gain card already checks this
                if (supplyCount(estate, state) > 0) {
                    gainCard(estate, state, 0, currentPlayer);

                    state->supplyCount[estate]++;//Decrement estates  (Gain card already decrements this)
                    if (supplyCount(estate, state) == 0) {
                        isGameOver(state);
                    }
                }
        }
        else {
            state->discard[currentPlayer][state->discardCount[currentPlayer]] = state->hand[currentPlayer][estateToDiscard];
            state->discardCount[currentPlayer]++;
            for (; estateToDiscard < state->handCount[currentPlayer]; estateToDiscard++) {
                state->hand[currentPlayer][estateToDiscard] = state->hand[currentPlayer][estateToDiscard+1];
            }
            state->hand[currentPlayer][state->handCount[currentPlayer]] = -1;
            state->handCount[currentPlayer]--;
        }
    else {// They chose not to discard an estate and must gain an estate
    	if (supplyCount(estate, state) > 0) {
            gainCard(estate, state, 0, currentPlayer);//Gain an estate

            state->supplyCount[estate]--;//Decrement Estates
            if (supplyCount(estate, state) == 0) {
                isGameOver(state); // This doesnt actually do anything?
            }
        }
    }
    return 0
}

int minionCard(int choice1, int choice2, int currentPlayer, struct gameState *state, int handPos) {
    //discard card from hand
    discardCard(handPos, currentPlayer, state, 1);

	if (choice1)
    {
        state->coins = state->coins + 2;
    }
    else if (choice2)		//discard hand, redraw 4, other players with 5+ cards discard hand and draw 4
    {
        //discard hand
        discardHand(currentPlayer, state);

        //draw 4
        drawMultCards(currentPlayer, 4, state);

        //other players discard hand and redraw if hand size > 4
        for (i = 0; i < state->numPlayers; i++)
        {
            if (i != currentPlayer)
            {
                if ( state->handCount[i] > 4 )
                {
                    //discard hand
                    discardHand(i, state);

                    //draw 4
                    drawMultCards(i, 4, state);
                }
            }
        }
    }
    return 0;
}

int ambassadorCard(int choice1,int choice2, int currentPlayer, struct gameState *state, int handPos) {
	j = 0;		//used to check if player has enough cards to discard
	// If they try to return an incorrect amount of cards
    if (choice2 > 2 || choice2 < 0)
    {
        return -1;
    }
    //  If they try to reveal the ambassador card that is currently being played.
    if (choice1 == handPos)
    {
        return -1;
    }

    for (i = 0; i < state->handCount[currentPlayer]; i++)
    {
        if (i == state->hand[currentPlayer][choice1] && i != choice1)
        {
            j++;
        }
    }
    if (j < choice2)
    {
        return -1;
    }

    if (DEBUG)
        printf("Player %d reveals card number: %d\n", currentPlayer, state->hand[currentPlayer][choice1]);

    //increase supply count for choosen card by amount being discarded
    state->supplyCount[state->hand[currentPlayer][choice1]] += choice2;

    //each other player gains a copy of revealed card
    for (i = 0; i < state->numPlayers; i++)
    {
        gainCard(state->hand[currentPlayer][choice1], state, 0, i);
    }

    //discard played card from hand
    discardCard(handPos, currentPlayer, state, 0);

    //trash copies of cards returned to supply
    for (j = 0; j < choice2; j++)
    {
        for (i = 0; i < state->handCount[currentPlayer]; i++)
        {
            if (state->hand[currentPlayer][i] == state->hand[currentPlayer][choice1])
            {
                discardCard(i, currentPlayer, state, 1);
                break;
            }
        }
    }

    return 0;
}

int tributeCard(int choice1, int currentPlayer, int nextPlayer,  struct gameState *state, int handPos) {
	if ((state->discardCount[nextPlayer] + state->deckCount[nextPlayer]) <= 1) {
        if (state->deckCount[nextPlayer] > 0) {
            tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
            state->deckCount[nextPlayer]--;
        }
        else if (state->discardCount[nextPlayer] > 0) {
            tributeRevealedCards[0] = state->discard[nextPlayer][state->discardCount[nextPlayer]-1];
            state->discardCount[nextPlayer]--;
        }
        else {
            //No Card to Reveal
            if (DEBUG) {
                printf("No cards to reveal\n");
            }
        }
    }

    else {
        if (state->deckCount[nextPlayer] == 0) {
            for (i = 0; i < state->discardCount[nextPlayer]; i++) {
                state->deck[nextPlayer][i] = state->discard[nextPlayer][i];//Move to deck
                state->deckCount[nextPlayer]++;
                state->discard[nextPlayer][i] = -1;
                state->discardCount[nextPlayer]--;
            }
        }
        tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
        state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
        state->deckCount[nextPlayer]--;
        tributeRevealedCards[1] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
        state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
        state->deckCount[nextPlayer]--;
    }

    if (tributeRevealedCards[0] != tributeRevealedCards[1]) { //If we have a duplicate card, just drop one
        state->playedCards[state->playedCardCount] = tributeRevealedCards[1];
        state->playedCardCount++;
        tributeRevealedCards[1] = -1;
    }

    for (i = 0; i <= 2; i++) {
        if (isTreasure(tributeRevealedCards[i])) { //Treasure cards
            state->coins += 2;
        }

        else if (isVictory(tributeRevealedCards[i])) { //Victory Card Found
            drawMultCards(currentPlayer, 2, state);
        }
        else { //Action Card
            state->numActions = state->numActions + 2;
        }
    }
    return 0;
}

int mineCard(int choice1, int choice2, int currentPlayer, struct gameState *state, int handPos) {
	j = state->hand[currentPlayer][choice1];  //store card we will trash

    if (isTreasure(j) == 0)
    {
        return -1;
    }

    if (choice2 > treasure_map || choice2 < curse)
    {
        return -1;
    }

    if ( (getCost(state->hand[currentPlayer][choice1]) + 3) > getCost(choice2) )
    {
        return -1;
    }

    gainCard(choice2, state, 2, currentPlayer);

    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);

    //discard trashed card
    for (i = 0; i < state->handCount[currentPlayer]; i++)
    {
        if (state->hand[currentPlayer][i] == j)
        {
            discardCard(i, currentPlayer, state, 0);
            break;
        }
    }
    return 0;
}