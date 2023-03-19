#include "TranspositionTable.h"

// Insert score for a given state
// Replace on collision
void TranspositionTable::insertValue(const GameState &state, int score) {
  this->transposition_map[this->getHash(state)] = {score};
}

// Check if a given state is in the transposition table
int TranspositionTable::containsValue(const GameState &state) {
  return this->transposition_map.count(this->getHash(state));
}

// Get the score for a given state
int TranspositionTable::getValue(const GameState &state) {
  return this->transposition_map[this->getHash(state)].score;
}

// Compute the Spooky hash value for a given game state
uint32 TranspositionTable::getHash(const GameState &state) {
  return SpookyHash::Hash32(&state, sizeof(state), this->hashSeed);
}
