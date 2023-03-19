#ifndef Agent_H
#define Agent_H

#include "Game.h";
#include "TranspositionTable.h";

typedef int move_val_t;

int getMove(move_val_t move_val) {
  return move_val >> 8;
}

int getVal(move_val_t move_val) {
  return move_val & 0xFF;
}

move_val_t makeMoveVal(int move, int val) {
  return (move << 8) | val;
}

class Agent {
  public:
    Agent(): MAX_SEARCH_DEPTH(10) {}
    Agent(int max_search_depth): MAX_SEARCH_DEPTH(max_search_depth) {}

    int getBestMove(const GameState &root);

  private:
    int iterativeDeepening(const GameState &root);
    int mtdf(const GameState &root, int f, int d);
    move_val_t alphaBetaWithMemory(const GameState &root, int alpha, int beta, int depth);

    int MAX_SEARCH_DEPTH;
    TranspositionTable transposition_table = TranspositionTable();
};

#endif