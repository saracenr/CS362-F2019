#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int drawNCards(int player, struct gameState *state, int numToDraw);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state,
                int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3,
               struct gameState *state, int handPos, int *bonus);
int cardMine(int currentPlayer, int choice1, int choice2, struct gameState *state, int handPos);
int cardBaron(int currentPlayer, int choice1, struct gameState *state);
int cardMinion(int currentPlayer,  int choice1, int choice2, struct gameState *state, int handPos);int cardAmbassador(int currentPlayer, int choice1, int choice2, struct gameState *state, int handPos);
int cardTribute(int currentPlayer, int nextPlayer, struct gameState *state, int *tributeRevealedCards);

#endif
