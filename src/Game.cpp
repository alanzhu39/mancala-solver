#include "Game.h";

int wrapBoard(int i) {
  return i % 14;
}

/* 
 * Given a game state and a move, return the new game state
 */
GameState makeMove(GameState &game_state, int move) {
  // Initialize new game state
  GameState new_game_state = game_state;

  // Get counter value at move, depending on current turn
  int turn = game_state.turn;
  int turn_offset = turn * 7;
  int counter_value = game_state.board[turn_offset + move];

  // Place stones based on counter value
  int k = 1;
  while (k <= counter_value) {
    int board_index = wrapBoard(turn_offset + move + k);
    if ((turn == 1 && board_index == 6) || (turn == 0 && board_index == 13)) {
      // Skip opponent's store
      k++;
    } else {
      new_game_state.board[board_index]++;
      k++;
    }
  }

  // Check if pits are all empty
  int pits_sum = 0;
  for (int i = 0; i < 6; i++) {
    pits_sum += new_game_state.board[turn_offset + i];
  }

  if (pits_sum == 0) {
    // Pits are all empty, add remaining stones to store
    int opponent_offset = turn_offset == 0 ? 7 : 0;
    for (int i = 0; i < 6; i++) {
      new_game_state.board[opponent_offset + 6] += new_game_state.board[opponent_offset + i];
      new_game_state.board[opponent_offset + i] = 0;
    }
  }

  // Check if last stone is in store
  int last_board_index = wrapBoard(turn_offset + move + k - 1);
  if ((turn == 0 && last_board_index == 6) || (turn == 1 && last_board_index == 13)) {
    // Last stone is in store, so turn is not over
    new_game_state.turn = turn;
  } else {
    // Last stone is not in store, so turn is over
    new_game_state.turn = (turn + 1) % 2;
  }

  return new_game_state;
}

int getScore(GameState &game_state) {
  if (game_state.turn == 0) {
    return game_state.board[6] - game_state.board[13];
  } else {
    return game_state.board[13] - game_state.board[6];
  }
}
