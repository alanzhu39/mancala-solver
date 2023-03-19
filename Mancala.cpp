#include "src/Game.h"
#include "src/Agent.h"

int main(int argc, char* argv[]) {
  // Initialize game state
  GameState game_state = startGame(0, 0);

  // Initialize agent
  Agent agent = Agent();

  // Play game
  char user_input;
  while (user_input != 'q') {
    std::cout << std::endl;
    printBoard(game_state);
    std::cout << "Current turn: " << (game_state.turn == 0 ? "North" : "South") << std::endl;
    std::cout << std::endl;
    std::cout << "Enter a move (0-5) or 'q' to quit: ";
    std::cin >> user_input;

    if (user_input == 'q') {
      break;
    }

    int move = user_input - '0';
    if (move < 0 || move > 5) {
      std::cout << "Invalid move" << std::endl;
      continue;
    }

    game_state = makeMove(game_state, move);
  }

  return 0;
}
