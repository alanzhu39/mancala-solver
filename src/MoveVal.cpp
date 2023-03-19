#include "MoveVal.h"

int getMove(const move_val_t &move_val) {
  return move_val.first;
}

int getVal(const move_val_t &move_val) {
  return move_val.second;
}

move_val_t makeMoveVal(int move, int val) {
  return {move, val};
}
