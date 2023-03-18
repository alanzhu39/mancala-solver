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

}
