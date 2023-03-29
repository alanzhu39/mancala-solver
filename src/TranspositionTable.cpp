#include "TranspositionTable.h"

// Insert score for a given state
void TranspositionTable::insertEntry(const GameState &state, int depth, int score, int move, int type) {
  hash_t hash = getHash(state);
  if (
    // Insert if the state is not in the table
    transposition_map.count(hash) == 0
    // Prefer exact scores over lower/upper bounds
    || type == 0
    // Prefer deeper scores over shallower scores (keep exact scores)
    || (transposition_map[hash].type != 0 && depth > transposition_map[hash].depth)
  ) {
    transposition_map[hash] = {depth, score, move, type};
  }
}

// Check if a given state is in the transposition table
int TranspositionTable::containsState(const GameState &state) {
  return transposition_map.count(getHash(state));
}

// Get the score for a given state
TranspositionTable::TranspositionEntry TranspositionTable::getEntry(const GameState &state) {
  return transposition_map[getHash(state)];
}

// Compute the Spooky hash value for a given game state
TranspositionTable::hash_t TranspositionTable::getHash(const GameState &state) {
  return SpookyHash::Hash64(&state, sizeof(state), hashSeed);
}
