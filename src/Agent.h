#ifndef Agent_H
#define Agent_H

#include "Game.h";

int MAX_SEARCH_DEPTH = 10;

int getBestMove(GameState &root);

int iterativeDeepening(GameState &root);
int mtdf(GameState &root, int f, int d);

#endif