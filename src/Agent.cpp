#include "Agent.h";
#include <algorithm>;

int getBestMove(const GameState &root) {
  return iterativeDeepening(root);
}

int iterativeDeepening(const GameState &root) {
  // TODO: use transposition table for first guess
  int first_guess = 0;
  for (int d = 1; d <= MAX_SEARCH_DEPTH; d++) {
    first_guess = mtdf(root, first_guess, d);
    // TODO: timeout
  }
  return first_guess;
}

int mtdf(const GameState &root, int f, int d) {
  int bound[2] = {-50, 50}; // lower, upper
  do {
    int beta = f + (f == bound[0]);
    f = alphaBetaWithMemory(root, beta - 1, beta, d);
    bound[f < beta] = f;
  } while (bound[0] < bound[1]);
  return f;
}

int alphaBetaWithMemory(const GameState &root, int alpha, int beta, int depth) {
  // TODO: add memory
  if (depth == 0) {
    return getScore(root);
  }
  if (root.turn == 0) {
    // Turn = 0
    int value = -50;
    for (int i = 0; i < 6; i++) {
      if (root.board[i] != 0) {
        value = std::max(value, alphaBetaWithMemory(makeMove(root, i), alpha, beta, depth - 1));
        if (value > beta) {
          break; // beta cutoff
        }
        alpha = std::max(alpha, value);
      }
    }
  } else {
    // Turn = 1
    int value = 50;
    int turn_offset = 7;
    for (int i = 0; i < 6; i++) {
      if (root.board[turn_offset + i] != 0) {
        value = std::min(value, alphaBetaWithMemory(makeMove(root, i), alpha, beta, depth - 1));
        if (value < alpha) {
          break; // alpha cutoff
        }
        beta = std::min(beta, value);
      }
    }
  }
}
