#ifndef TranspositionTable_H
#define TranspositionTable_H

#include <iostream>
#include <vector>
#include <unordered_map>

#include "Game.h";
#include "SpookyHash.h";

class TranspositionTable {
  public:
    // Insert score for a given state
    // Replace on collision
    void insertValue(const GameState &state, int score);

    // Check if a given state is in the transposition table
    int containsValue(const GameState &state);

    // Get the score for a given state
    int getValue(const GameState &state);

  private:
    // Define a struct to represent a transposition table entry
    struct TranspositionEntry {
      int score;  // Score of the position
    };

    // Compute the Spooky hash value for a given game state
    uint32 getHash(const GameState &state);

    // Define a function to initialize the transposition table
    std::unordered_map<uint32, TranspositionEntry> transposition_map;

    // Seed for Spooky hash
    uint32 hashSeed = 0;
};

#endif