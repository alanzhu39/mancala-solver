#ifndef TranspositionTable_H
#define TranspositionTable_H

#include <iostream>
#include <vector>
#include <unordered_map>

#include "Game.h"
#include "SpookyHash.h"

class TranspositionTable {
  public:
    // Define a struct to represent a transposition table entry
    struct TranspositionEntry {
      int depth;  // Depth to which the position was evaluated
      int score;  // Score of the position
      int move;   // Move that led to the position
      int type;   // Entry type (exact, lower bound, upper bound)
    };

    // Insert score for a given state
    void insertEntry(const GameState &state, int depth, int score, int move, int type);

    // Check if a given state is in the transposition table
    int containsState(const GameState &state);

    // Get the score for a given state
    TranspositionEntry getEntry(const GameState &state);

  private:
    typedef uint64 hash_t;
  
    // Compute the Spooky hash value for a given game state
    hash_t getHash(const GameState &state);

    // Define a function to initialize the transposition table
    std::unordered_map<hash_t, TranspositionEntry> transposition_map;

    // Seed for Spooky hash
    hash_t hashSeed = 0;
};

#endif