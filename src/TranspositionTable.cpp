#include "TranspositionTable.h";

const int kNumBowls = 6;  // Number of bowls per side
const int kNumSides = 2;  // Number of sides
const int kNumStones = 48;  // Total number of stones

// Define a struct to represent the game state
struct State {
    std::vector<int> bowls[kNumSides];  // Number of stones in each bowl for each side
    int stores[kNumSides];  // Number of stones in each store for each side
    int player;  // Current player (0 or 1)
};

// Define a function to compute the Zobrist hash value for a given game state
std::size_t GetHash(const State& state, const std::vector<std::vector<std::size_t>>& zobrist_table) {
    std::size_t hash = 0;
    for (int i = 0; i < kNumSides; i++) {
        for (int j = 0; j < kNumBowls; j++) {
            hash ^= zobrist_table[i][j * (kNumStones + 1) + state.bowls[i][j]];
        }
        hash ^= zobrist_table[i][kNumBowls * (kNumStones + 1) + state.stores[i]];
    }
    hash ^= state.player;
    return hash;
}

// Define a function to initialize the Zobrist table
std::vector<std::vector<std::size_t>> InitZobristTable() {
    std::vector<std::vector<std::size_t>> zobrist_table(kNumSides, std::vector<std::size_t>((kNumBowls + 1) * (kNumStones + 1), 0));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::size_t> dis(0, std::numeric_limits<std::size_t>::max());
    for (int i = 0; i < kNumSides; i++) {
        for (int j = 0; j < kNumBowls; j++) {
            for (int k = 0; k <= kNumStones; k++) {
                zobrist_table[i][j * (kNumStones + 1) + k] = dis(gen);
            }
        }
        zobrist_table[i][kNumBowls * (kNumStones + 1)] = dis(gen);
    }
    return zobrist_table;
}

// Define a struct to represent a transposition table entry
struct TranspositionEntry {
    int depth;  // Depth of the search at which this entry was stored
    int score;  // Score of the position
};

// Define a function to initialize the transposition table
std::unordered_map<std::size_t, TranspositionEntry> InitTranspositionTable() {
    std::unordered_map<std::size_t, TranspositionEntry> transposition_table;
    return transposition_table;
}

int main() {
    // Initialize the Zobrist table and the transposition table
    std::vector<std::vector<std::size_t>> zobrist_table = InitZobristTable();
    std::unordered_map<std::size_t, TranspositionEntry> transposition_table = InitTranspositionTable();
    return 0;
}
