#include "Agent.h"

int LOWER_INF = -1000;
int UPPER_INF = 1000;

int Agent::getBestMove(const GameState &root) {
  return getMove(iterativeDeepening(root));
}

move_val_t Agent::iterativeDeepening(const GameState &root) {
  // TODO: use transposition table for first guess
  move_val_t move_val;
  int first_guess = 0;
  for (int d = 1; d <= MAX_SEARCH_DEPTH; d++) {
    move_val = mtdf(root, first_guess, d);
    first_guess = getVal(move_val);
    // TODO: timeout
  }
  return move_val;
}

move_val_t Agent::mtdf(const GameState &root, int f, int d) {
  int bounds[2] = {LOWER_INF, UPPER_INF}; // lower, upper
  move_val_t move_val;

  do {
    int beta = f + (f == bounds[0]);
    move_val = alphaBetaWithMemory(root, beta - 1, beta, d);

    f = getVal(move_val);

    bounds[f < beta] = f;
  } while (bounds[0] < bounds[1]);

  return move_val;
}

move_val_t Agent::alphaBetaWithMemory(const GameState &root, int alpha, int beta, int depth) {
  // TODO: add memory
  if (depth == 0 || root.isOver == 1) {
    return makeMoveVal(-1, getScore(root));
  }
  if (root.turn == 0) {
    // Turn = 0
    int value = LOWER_INF;
    move_val_t move_val = makeMoveVal(-1, value);
    for (int i = 0; i < 6; i++) {
      if (root.board[i] != 0) {
        int new_value = getVal(alphaBetaWithMemory(makeMove(root, i), alpha, beta, depth - 1));
        if (new_value > value) {
          value = new_value;
          move_val = makeMoveVal(i, value);
        }
        if (value > beta) {
          break; // beta cutoff
        }
        alpha = std::max(alpha, value);
      }
    }
    return move_val;
  } else {
    // Turn = 1
    int value = UPPER_INF;
    move_val_t move_val = makeMoveVal(-1, value);
    int turn_offset = 7;
    for (int i = 0; i < 6; i++) {
      if (root.board[turn_offset + i] != 0) {
        int new_value = getVal(alphaBetaWithMemory(makeMove(root, i), alpha, beta, depth - 1));
        if (new_value < value) {
          value = new_value;
          move_val = makeMoveVal(i, value);
        }
        if (value < alpha) {
          break; // alpha cutoff
        }
        beta = std::min(beta, value);
      }
    }
    return move_val;
  }
}
