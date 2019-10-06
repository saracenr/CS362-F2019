#ifndef _CARDFUNCTIONS_H
#define _CARDFUNCTIONS_H

int handIterator(int cardToFind, struct gameState *state, int currentCard);
int baronCard(int choice1, struct gameState *state, int handPos);
int minionCard(int choice1, int choice2, struct gameState *state, int handPos);
int ambassadorCard(int choice1, int choice2, struct gameState *state, int handPos);
int tributeCard(int choice1, struct gameState *state, int handPos);
int mineCard(int choice1, int choice2, struct gameState *state, int handPos);

#endif