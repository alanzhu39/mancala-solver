#include "src/Game.h"
#include "src/Agent.h"

int main(int argc, char* argv[]) {
  // Initialize game state
  GameState game_state = startGame(0, 0);

  // GameState game_state = {
  //   {
  //     0, 0, 1, 0, 1, 4, 9, 0, 1, 1, 0, 0, 3, 4
  //   }, // board
  //   1, // turn
  //   0 // isOver
  // };

  // Initialize agent
  int searchDepth = 19;
  Agent agentNorth = Agent(searchDepth);
  Agent agentSouth = Agent(searchDepth);

  // Play game
  while (!game_state.isOver) {
    int move;
    if (game_state.turn == 1) {
      // South's turn (AI)
      move = agentSouth.getBestMove(game_state);
      std::cout << move;
    } else {
      move = agentNorth.getBestMove(game_state);
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
  /*
  // Initialize agent
  Agent agent = Agent();

  // Play game
  char user_input;
  while (user_input != 'q') {
    std::cout << std::endl;
    printBoard(game_state);
    std::cout << "Current turn: " << (game_state.turn == 0 ? "North" : "South") << std::endl;
    std::cout << std::endl;

    int move;
    if (game_state.turn == 1) {
      // South's turn (AI)
      move = agent.getBestMove(game_state);
      std::cout << "Agent's move: " << move << std::endl;
    } else {
      // North's turn (human)
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
  */

  return 0;
}
