#ifndef TranspositionTable_H
#define TranspositionTable_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "Game.h";

// Define a function to compute the Zobrist hash value for a given game state
std::size_t GetHash(const GameState &state, const std::vector<std::vector<std::size_t>>& zobrist_table);

// Define a function to initialize the Zobrist table
std::vector<std::vector<std::size_t>> InitZobristTable();

// Define a struct to represent a transposition table entry
struct TranspositionEntry {
  int depth;  // Depth of the search at which this entry was stored
  int score;  // Score of the position
};

// Define a function to initialize the transposition table
std::unordered_map<std::size_t, TranspositionEntry> InitTranspositionTable();

#endif