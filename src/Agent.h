#ifndef Agent_H
#define Agent_H

#include "Game.h"
#include "TranspositionTable.h"
#include "MoveVal.h"
#include <algorithm>

class Agent {
  public:
    Agent(): MAX_SEARCH_DEPTH(10) {}
    Agent(int max_search_depth): MAX_SEARCH_DEPTH(max_search_depth) {}

    int getBestMove(const GameState &root);

  private:
    move_val_t iterativeDeepening(const GameState &root);
    move_val_t mtdf(const GameState &root, int f, int d);
    move_val_t alphaBetaWithMemory(const GameState &root, int alpha, int beta, int depth);

    int MAX_SEARCH_DEPTH;
    TranspositionTable transposition_table = TranspositionTable();
};

#endif