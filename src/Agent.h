#ifndef Agent_H
#define Agent_H

#include "Game.h"
#include "TranspositionTable.h"
#include "MoveVal.h"
#include <algorithm>
#include <chrono>

class Agent {
  public:
    Agent(): MAX_SEARCH_DEPTH(30), use_memory(1) {}
    Agent(int max_search_depth, int use_memory): MAX_SEARCH_DEPTH(max_search_depth), use_memory(use_memory) {}

    int getBestMove(const GameState &root);
    int getBestMove(const GameState &root, int timed);

  private:
    move_val_t iterativeDeepening(const GameState &root);
    move_val_t mtdf(const GameState &root, int f, int d);
    move_val_t alphaBeta(const GameState &root, int alpha, int beta, int depth);
    move_val_t alphaBetaWithMemory(const GameState &root, int alpha, int beta, int depth);

    int MAX_SEARCH_DEPTH;
    int use_memory;
    TranspositionTable transposition_table = TranspositionTable();
};

#endif