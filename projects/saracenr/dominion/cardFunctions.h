#ifndef _CARDFUNCTIONS_H
#define _CARDFUNCTIONS_H

#include "dominion.h"

int cardFinder(int cardToFind, int player, struct gameState *state, int currentCardHandPos);
void discardHand(int player, struct gameState *state);
void drawMultCards(int player, int numberOfCards, struct gameState *state);
int isTreasure(int card);
int isVictory(int card);


int baronCard(int choice1, int currentPlayer, struct gameState *state, int handPos);
int minionCard(int choice1, int choice2, int currentPlayer, struct gameState *state, int handPos);
int ambassadorCard(int choice1, int choice2, int currentPlayer, struct gameState *state, int handPos);
int tributeCard(int choice1, int currentPlayer, int nextPlayer, struct gameState *state, int handPos);
int mineCard(int choice1, int choice2, int currentPlayer, struct gameState *state, int handPos);

#endif