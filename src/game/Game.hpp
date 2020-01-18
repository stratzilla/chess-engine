#include "../player/Player.hpp"

// Game class declaration

class Game {
	private:
		Board* gameboard; // the current board
		Player* playerA; Player* playerB; // players
		unsigned int gameState; // current game state
		unsigned int moveCount = 1; // game move counter

		// private member methods
		void whiteMove();
		void blackMove();
		void makeMove(Move);
		Board* getBoard();

		// private accessor methods
		Player& getPlayerWhite();
		Player& getPlayerBlack();
		int getGameState();

		// private mutator methods
		void setGameState(int);
	public:
		Game(Board*, Player*, Player*); // constructor

		// public member methods
		void play();
};
