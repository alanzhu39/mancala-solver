#ifndef Game_H
#define Game_H

#include <iostream>
#include <cstring>
#include <algorithm>

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
  char isOver;
  // TODO: game mode
};

GameState startGame(int game_mode, int difficulty, int num_stones);
GameState startGameNumStones(int num_stones);
GameState makeMove(const GameState &game_state, int move);

int getScore(const GameState &game_state);
int maxFutility(const GameState &game_state);
int minFutility(const GameState &game_state);
void printBoard(const GameState &game_state);

#endif