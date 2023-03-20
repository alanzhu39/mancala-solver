#include "Agent.h"

int LOWER_INF = -1000;
int UPPER_INF = 1000;

int collision_counter = 0;
int node_counter = 0;

int Agent::getBestMove(const GameState &root) {
  return getMove(iterativeDeepening(root));
}

int Agent::getBestMove(const GameState &root, int timed) {
  if (timed == 0) {
    return getBestMove(root);
  }

  auto start = std::chrono::high_resolution_clock::now();

  int move = getMove(iterativeDeepening(root));

  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

  std::cout << node_counter << std::endl;
  std::cout << collision_counter << std::endl;
  std::cout << move << std::endl;
  std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;

  return move;
}

move_val_t Agent::iterativeDeepening(const GameState &root) {
  // TODO: use transposition table for first guess?
  move_val_t move_val;
  int first_guess = 0;
  int step_size = 3;
  for (int d = 1; d <= MAX_SEARCH_DEPTH; d += step_size) {
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
    if (use_memory) {
      move_val = alphaBetaWithMemory(root, beta - 1, beta, d);
    } else {
      move_val = alphaBeta(root, beta - 1, beta, d);
    }

    f = getVal(move_val);

    bounds[f < beta] = f;
  } while (bounds[0] < bounds[1]);

  return move_val;
}

move_val_t Agent::alphaBeta(const GameState &root, int alpha, int beta, int depth) {
  node_counter++;
  if (depth == 0 || root.isOver == 1) {
    return makeMoveVal(-1, getScore(root));
  }

  if (root.turn == 0) {
    // Turn = 0
    int value = LOWER_INF;
    int move = -1;
    for (int i = 0; i < 6; i++) {
      if (root.board[i] != 0) {
        int new_value = getVal(alphaBeta(makeMove(root, i), alpha, beta, depth - 1));
        if (new_value > value) {
          value = new_value;
          move = i;
        }
        if (value > beta) {
          break; // beta cutoff
        }
        alpha = std::max(alpha, value);
      }
    }
    return makeMoveVal(move, value);
  } else {
    // Turn = 1
    int value = UPPER_INF;
    int move = -1;
    int turn_offset = 7;
    for (int i = 0; i < 6; i++) {
      if (root.board[turn_offset + i] != 0) {
        int new_value = getVal(alphaBeta(makeMove(root, i), alpha, beta, depth - 1));
        if (new_value < value) {
          value = new_value;
          move = i;
        }
        if (value < alpha) {
          break; // alpha cutoff
        }
        beta = std::min(beta, value);
      }
    }
    return makeMoveVal(move, value);
  }
}

move_val_t Agent::alphaBetaWithMemory(const GameState &root, int alpha, int beta, int depth) {
  node_counter++;
  // TODO: add memory
  if (depth == 0 || root.isOver == 1) {
    return makeMoveVal(-1, getScore(root));
  }

  int start_move = 0;
  if (transposition_table.containsState(root)) {
    collision_counter++;
    TranspositionTable::TranspositionEntry transposition_entry = transposition_table.getEntry(root);
    if (transposition_entry.type == 0) {
      return makeMoveVal(transposition_entry.move, getScore(root) + transposition_entry.score);
    } else if (transposition_entry.type == 1) {
      beta = std::min(beta, transposition_entry.score);
    } else if (transposition_entry.type == 2) {
      alpha = std::max(alpha, transposition_entry.score);
    }
    start_move = transposition_entry.move;
  }

  if (root.turn == 0) {
    // Turn = 0
    int value = LOWER_INF;
    int move = -1;
    if (maxFutility(root) )
    for (int j = 0; j < 6; j++) {
      int i = (start_move + j) % 6;
      if (root.board[i] != 0) {
        int new_value = getVal(alphaBetaWithMemory(makeMove(root, i), alpha, beta, depth - 1));
        if (new_value > value) {
          value = new_value;
          move = i;
        }
        if (value > beta) {
          // beta cutoff
          transposition_table.insertEntry(root, depth, value, move, 1);
          return makeMoveVal(move, value);
        }
        alpha = std::max(alpha, value);
      }
    }
    return makeMoveVal(move, value);
  } else {
    // Turn = 1
    int value = UPPER_INF;
    int move = -1;
    int turn_offset = 7;
    for (int j = 0; j < 6; j++) {
      int i = (start_move + j) % 6;
      if (root.board[turn_offset + i] != 0) {
        int new_value = getVal(alphaBetaWithMemory(makeMove(root, i), alpha, beta, depth - 1));
        if (new_value < value) {
          value = new_value;
          move = i;
        }
        if (value < alpha) {
          // alpha cutoff
          transposition_table.insertEntry(root, depth, value, move, 2);
          return makeMoveVal(move, value);
        }
        beta = std::min(beta, value);
      }
    }
    return makeMoveVal(move, value);
  }
}
