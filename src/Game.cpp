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
  int i = 1;
  while (i <= counter_value) {
    int board_index = wrapBoard(turn_offset + move + i);
    if ((turn == 1 && board_index == 6) || (turn == 0 && board_index == 13)) {
      // Skip opponent's store
      i++;
    } else {
      new_game_state.board[board_index]++;
      i++;
    }
  }

  // Check if last stone is in store
  int last_board_index = wrapBoard(turn_offset + move + i - 1);
  if ((turn == 0 && last_board_index == 6) || (turn == 1 && last_board_index == 13)) {
    // Last stone is in store, so turn is not over
    new_game_state.turn = turn;
  } else {
    // Last stone is not in store, so turn is over
    new_game_state.turn = (turn + 1) % 2;
  }

  return new_game_state;
}
