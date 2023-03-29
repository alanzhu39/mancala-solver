#ifndef Agent_H
#define Agent_H

#include "Game.h"
#include "TranspositionTable.h"
#include "Node.h"
#include <algorithm>
#include <chrono>

class Agent {
  public:
    Agent(): MAX_SEARCH_DEPTH(21), use_memory(1) {}
    Agent(int max_search_depth, int use_memory): MAX_SEARCH_DEPTH(max_search_depth), use_memory(use_memory) {}

    int getBestMove(const GameState &root);
    int getBestMove(const GameState &root, int timed);

  private:
    Node iterativeDeepening(const GameState &root);
    Node mtdf(const GameState &root, int f, int d);
    Node alphaBeta(const GameState &root, int alpha, int beta, int depth);
    Node alphaBetaWithMemory(const GameState &root, int alpha, int beta, int depth);

    int MAX_SEARCH_DEPTH;
    int use_memory;
    TranspositionTable transposition_table = TranspositionTable();
};

#endif