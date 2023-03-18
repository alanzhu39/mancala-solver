#ifndef Game_H
#define Game_H

typedef unsigned int counter;

struct GameState {
  counter board[14];
  int turn;
};

GameState makeMove(GameState &game_state, int move);

#endif