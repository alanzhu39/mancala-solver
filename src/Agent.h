#ifndef Agent_H
#define Agent_H

#include "Game.h";

int MAX_SEARCH_DEPTH = 10;

int getBestMove(const GameState &root);

int iterativeDeepening(const GameState &root);
int mtdf(const GameState &root, int f, int d);

#endif