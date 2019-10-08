#ifndef _CARDFUNCTIONS_H
#define _CARDFUNCTIONS_H

int handIterator(int cardToFind,int player, struct gameState *state, int currentCard);
int baronCard(int choice1, int currentPlayer, struct gameState *state, int handPos);
int minionCard(int choice1, int choice2, int currentPlayer, struct gameState *state, int handPos);
int ambassadorCard(int choice1, int choice2, int currentPlayer, struct gameState *state, int handPos);
int tributeCard(int choice1, int currentPlayer, int nextPlayer, struct gameState *state, int handPos);
int mineCard(int choice1, int choice2, int currentPlayer, struct gameState *state, int handPos);

#endif