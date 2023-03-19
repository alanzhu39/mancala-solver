#include "Agent.h";
#include <algorithm>;

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

int getBestMove(const GameState &root) {
  return getMove(iterativeDeepening(root));
}

move_val_t iterativeDeepening(const GameState &root) {
  // TODO: use transposition table for first guess
  move_val_t move_val = 0;
  int first_guess = 0;
  for (int d = 1; d <= MAX_SEARCH_DEPTH; d++) {
    move_val = mtdf(root, first_guess, d);
    first_guess = getVal(move_val);
    // TODO: timeout
  }
  return move_val;
}

move_val_t mtdf(const GameState &root, int f, int d) {
  int bounds[2] = {-50, 50}; // lower, upper
  move_val_t move_val;

  do {
    int beta = f + (f == bounds[0]);
    move_val = alphaBetaWithMemory(root, beta - 1, beta, d);

    f = getVal(move_val);

    bounds[f < beta] = f;
  } while (bounds[0] < bounds[1]);

  return move_val;
}

move_val_t alphaBetaWithMemory(const GameState &root, int alpha, int beta, int depth) {
  // TODO: add memory
  if (depth == 0) {
    return makeMoveVal(0, getScore(root));
  }
  if (root.turn == 0) {
    // Turn = 0
    move_val_t move_val = 0;
    int value = -50;
    for (int i = 0; i < 6; i++) {
      if (root.board[i] != 0) {
        move_val = std::max(value, alphaBetaWithMemory(makeMove(root, i), alpha, beta, depth - 1));
        value = getVal(move_val);
        if (value > beta) {
          break; // beta cutoff
        }
        alpha = std::max(alpha, value);
      }
    }
    return move_val;
  } else {
    // Turn = 1
    move_val_t move_val = 0;
    int value = 50;
    int turn_offset = 7;
    for (int i = 0; i < 6; i++) {
      if (root.board[turn_offset + i] != 0) {
        move_val = std::min(value, alphaBetaWithMemory(makeMove(root, i), alpha, beta, depth - 1));
        value = getVal(move_val);
        if (value < alpha) {
          break; // alpha cutoff
        }
        beta = std::min(beta, value);
      }
    }
    return move_val;
  }
}
