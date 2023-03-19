#include "Game.h"

int wrapBoard(int i) {
  return i % 14;
}

/* 
 * Start a game of Mancala
 * Game mode = 0: Capture mode
 * Game mode = 1: Avalanche mode
 * Difficulty = 0: 4 stones per pit
 * Difficulty = 1: Random stones per pit
 */
GameState startGame(int game_mode, int difficulty) {
  // TODO: game mode
  GameState game_state;
  game_state.turn = 0;
  game_state.isOver = 0;

  // Initialize board
  for (int i = 0; i < 14; i++) {
    if (i == 6 || i == 13) {
      game_state.board[i] = 0;
    } else {
      if (difficulty == 0) {
        // game_state.board[i] = 4;
        // FIXME: testing
        game_state.board[i] = 2;
      } else {
        // TODO: random difficulty
        game_state.board[i] = 0;
      }
    }
  }

  return game_state;
}

/* 
 * Given a game state and a move, return the new game state
 */
GameState makeMove(const GameState &game_state, int move) {
  // Initialize new game state
  GameState new_game_state;
  new_game_state.turn = game_state.turn;
  std::memcpy(new_game_state.board, game_state.board, sizeof(game_state.board));

  // Get counter value at move, depending on current turn
  int turn = game_state.turn;
  int turn_offset = turn * 7;
  int counter_value = game_state.board[turn_offset + move];
  new_game_state.board[turn_offset + move] = 0;

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
  int last_board_index = wrapBoard(turn_offset + move + k - 1);

  // Check if last stone is a capture
  if ((last_board_index >= turn_offset && last_board_index < turn_offset + 6) // Last stone is in player's side
    && new_game_state.board[last_board_index] == 1 // Last stone is in a pit that was empty
    && new_game_state.board[12 - last_board_index] > 0 // Opposing pit is not empty
  ) {
    // Add captured stones to store
    new_game_state.board[turn_offset + 6] += new_game_state.board[last_board_index] + new_game_state.board[12 - last_board_index];
    new_game_state.board[last_board_index] = 0;
    new_game_state.board[12 - last_board_index] = 0;
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

    // Game is over
    new_game_state.isOver = 1;
  }

  // Check if last stone is in store
  if ((turn == 0 && last_board_index == 6) || (turn == 1 && last_board_index == 13)) {
    // Last stone is in store, so turn is not over
    new_game_state.turn = turn;
  } else {
    // Last stone is not in store, so turn is over
    new_game_state.turn = (turn + 1) % 2;
  }

  return new_game_state;
}

int getScore(const GameState &game_state) {
  return game_state.board[6] - game_state.board[13];
}

void printBoard(const GameState &game_state) {
  std::cout << "| ";
  for (int i = 6; i >= 0; i--) {
    std::cout << (int)game_state.board[i] << " | ";
  }
  std::cout << "  |";
  std::cout << std::endl;
  std::cout << "---------------------------------" << std::endl;
  std::cout << "|  ";
  for (int i = 7; i <= 13; i++) {
    std::cout << " | " << (int)game_state.board[i];
  }
  std::cout << " |";
  std::cout << std::endl;
}
