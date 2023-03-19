#include "MoveVal.h"

int getMove(move_val_t move_val) {
  return move_val >> 8;
}

int getVal(move_val_t move_val) {
  return move_val & 0xFF;
}

move_val_t makeMoveVal(int move, int val) {
  return (move << 8) | val;
}
