#include "src/Game.h"
#include "src/Agent.h"
#include <chrono>

int main(int argc, char* argv[]) {
  if (argc >= 2) {
    // Debug mode
    int timing_mode = 1;

    // Initialize game state
    int num_stones;
    sscanf(argv[1], "%d", &num_stones);
    GameState game_state = startGameNumStones(num_stones);

    // Initialize agent
    int searchDepth = 19;
    std::cout << "Search depth: " << searchDepth << std::endl;
    Agent agentNorth = Agent(searchDepth);
    Agent agentSouth = Agent(searchDepth);

    // Play game
    while (!game_state.isOver) {
      int move;
      if (game_state.turn == 0) {
        // North's turn (AI)
        auto start = std::chrono::high_resolution_clock::now();

        move = agentNorth.getBestMove(game_state);

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        if (timing_mode == 1) {
          std::cout << move << std::endl;
          std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
          break;
        } else {
          std::cout << move;
        }
      } else {
        move = agentSouth.getBestMove(game_state);
        std::cout << move;
      }

      int old_turn = game_state.turn;
      game_state = makeMove(game_state, move);
      if (game_state.turn != old_turn) {
        std::cout << std::endl;
        printBoard(game_state);
      }
    }
    std::cout << std::endl;
    printBoard(game_state);

    return 0;
  }

  // Initialize game state
  GameState game_state = startGame(0, 0);

  // Initialize agent
  Agent agent = Agent(15);

  // Play game
  char user_input;
  while (user_input != 'q') {
    std::cout << std::endl;
    printBoard(game_state);
    std::cout << "Current turn: " << (game_state.turn == 0 ? "North" : "South") << std::endl;
    std::cout << std::endl;

    int move;
    if (game_state.turn == 0) {
      // North's turn (AI)
      move = agent.getBestMove(game_state);
      std::cout << "Agent's move: " << move << std::endl;
    } else {
      // South's turn (human)
      std::cout << "Enter a move (0-5) or 'q' to quit: ";
      std::cin >> user_input;

      if (user_input == 'q') {
        break;
      }

      move = user_input - '0';
      if (move < 0 || move > 5) {
        std::cout << "Invalid move" << std::endl;
        continue;
      }
    }

    game_state = makeMove(game_state, move);
  }

  return 0;
}
