#ifndef Game_H
#define Game_H

typedef char counter;

/*
 * Board is organized as:
 * 0 1 2 3 4 5: Player 1's side
 * 6: Player 1's store
 * 7 8 9 10 11 12: Player 2's side
 * 13: Player 2's store
 */
struct GameState {
  counter board[14];
  char turn;
};

GameState makeMove(GameState &game_state, int move);
int getScore(GameState &game_state);

#endif