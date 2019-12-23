#include "game/Game.hpp"
#include "player/Player.hpp"
#include "player/Human.hpp"
#include "player/Computer.hpp"

const bool WHITE = true, BLACK = false;

// remind user of proper compilation and execution
void printHelp() {
	std::cout << "\nCompile and execute the program as so:\n\n";
	std::cout << " $ g++ source.cpp */*.cpp -std=c++0x -Wno-deprecated -o chess\n";
	std::cout << " $ ./chess <args>\n\n";
	
	std::cout << "You may use two arguments:\n";
	std::cout << " <arg1> - Type of Game\n";
	std::cout << "  1. Human vs. Human\n";
	std::cout << "  2. Human vs. Computer\n";
	std::cout << "  3. Computer vs. Computer\n";
	std::cout << " <arg2> - Depth for Tree Search\n";
	std::cout << "  Some integer value >0\n\n";
	
	std::cout << "Or three arguments:\n";
	std::cout << " <arg1> - Type of Game\n";
	std::cout << " <arg2> - Depth for Tree Search\n";
	std::cout << " <arg3> - Relative Path to Save File\n\n";
	
	std::cout << "When prompted, enter one of the below commands:\n";
	std::cout << " - a move (in the form of a0b1, i.e. a0 to b1)\n";
	std::cout << " - a single coordinate to see possible moves\n";
	std::cout << " - \"save\" to save the current board\n";
	std::cout << " - \"quit\" to quit the current game\n\n";
	
	std::cout << "Save files are stored as text files in saves directory.\n";
	std::cout << "This will load a custom board state as described in that file.\n\n";
}

// main program driver
int main(int argc, char** argv) {
	// create two empty players, init later
	Player* white; Player* black; Board* gameboard;
	if (argc < 3 || argc > 4) { // if not enough arguments
		printHelp(); return 0; 
	} else {
		// if invalid depth
		if (atoi(argv[2]) < 1) { printHelp(); return 0; }
		unsigned int depth = atoi(argv[2]);
		switch(atoi(argv[1])) { // determine type of game
			case 1: 
				white = new Human(WHITE);
				black = new Human(BLACK); 
				break;
			case 2: 
				white = new Human(WHITE);
				black = new Computer(BLACK, depth); 
				break;
			case 3:
				white = new Computer(WHITE, depth);
				black = new Computer(BLACK, depth);
				break;
			default: printHelp(); return 0;
		}
		switch(argc) { // determine if custom or not
			case 3: gameboard = new Board(); break; // default normal
			case 4: { // custom board
				std::ifstream file(argv[3]); // try to open file
				// if file doesn't exist, this will proc
				if (!file.is_open()) { printHelp(); file.close(); return 0; }
				// otherwise init board
				file.close();
				gameboard = new Board(argv[3]); break; }
			default: printHelp(); return 0;
		}
		Game g(gameboard, white, black); // init game
		g.play(); // play the game
	}
	return 1;
}