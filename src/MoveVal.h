#ifndef MoveVal_H
#define MoveVal_H

#include <utility>

typedef std::pair<int, int> move_val_t;

int getMove(const move_val_t &move_val);

int getVal(const move_val_t &move_val);

move_val_t makeMoveVal(int move, int val);

#endif