#include "game/Game.hpp"
#include "player/Human.hpp"
#include "player/Computer.hpp"

const bool WHITE = true, BLACK = false;

// remind user of proper compilation and execution
inline void printHelp() {
	std::cout << "\nCompile and execute the program as so:\n\n";
	std::cout << " $ g++ source.cpp */*.cpp -o chess\n";
	std::cout << " $ ./chess <args>\n\n";

	std::cout << "You may use no arguments for a Human vs. Human game.\n\n";

	std::cout << "Or two arguments:\n";
	std::cout << " <arg1> - Type of Game\n";
	std::cout << "  1. Human vs. Computer\n";
	std::cout << "  2. Computer vs. Human\n";
	std::cout << "  3. Computer vs. Computer\n";
	std::cout << " <arg2> - Depth for Tree Search\n";
	std::cout << "  - some integer value >0\n\n";

	std::cout << "When prompted, enter one of the below commands:\n";
	std::cout << " - a move (in the form of a0b1, i.e. a0 to b1)\n";
	std::cout << " - a single coordinate to see possible moves\n";
	std::cout << " - \"quit\" to quit the current game\n\n";
}

// main program driver
int main(int argc, char** argv) {
	// create two empty players, init later
	Player* white; Player* black;
	// init game board
	Board* gameboard = new Board();
	if (argc != 1 && argc != 3) { // if invalid num args
		printHelp(); return 1;
	} else { // no argument or two arguments
		if (argc == 1) { // human vs human
			white = new Human(WHITE);
			black = new Human(BLACK);
		} else { // some ai is involved
			// if invalid depth
			if (atoi(argv[2]) < 1) { printHelp(); return 1; }
			unsigned int depth = atoi(argv[2]); // depth valid, init
			switch(atoi(argv[1])) { // determine type of game
				case 1: // human vs ai
					white = new Human(WHITE);
					black = new Computer(BLACK, depth);
					break;
				case 2: // ai vs human
					white = new Computer(WHITE, depth);
					black = new Human(BLACK);
					break;
				case 3: // ai vs ai
					white = new Computer(WHITE, depth);
					black = new Computer(BLACK, depth);
					break;
				default: printHelp(); return 1;
			}
		}
	}
	Game g(gameboard, white, black); // init game
	g.play(); // play the game
	return 0;
}
