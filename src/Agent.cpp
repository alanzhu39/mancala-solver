#include "Agent.h";

int getBestMove(GameState &root) {
  return iterativeDeepening(root);
}

int iterativeDeepening(GameState &root) {
  firstguess := 0;
    for d = 1 to MAX_SEARCH_DEPTH do
      firstguess := MTDF(root, firstguess, d);
      if times_up() then break;
    return firstguess;
}

int mtdf(GameState &root, int f, int d) {
  int bound[2] = {-50, 50}; // lower, upper
  do {
    beta = f + (f == bound[0]);
    f = alphaBetaWithMemory(beta - 1, beta, depth);
    bound[f < beta] = f;
  } while (bound[0] < bound[1]);
  return f;
}

int alphaBetaWithMemory(GameState &root, int alpha, int beta, int depth) {
  if (depth == 0) {
    return getScore(root);
  }
  if (root.turn == 0) {
    value = -50;
    for (int i = 0; i < 6; i++) {
      if (root.board[i] != 0) {
        alpha = max(alpha, -alphaBetaWithMemory(makeMove(root, i), -beta, -alpha, depth - 1));
        if (alpha >= beta) {
          return alpha;
        }
      }
    }
  } else {
    beta = 50;
  }
}


function alphabeta(node, depth, α, β, maximizingPlayer) is
    if depth = 0 or node is a terminal node then
        return the heuristic value of node
    if maximizingPlayer then
        value := −∞
        for each child of node do
            value := max(value, alphabeta(child, depth − 1, α, β, FALSE))
            if value > β then
                break (* β cutoff *)
            α := max(α, value)
        return value
    else
        value := +∞
        for each child of node do
            value := min(value, alphabeta(child, depth − 1, α, β, TRUE))
            if value < α then
                break (* α cutoff *)
            β := min(β, value)
        return value