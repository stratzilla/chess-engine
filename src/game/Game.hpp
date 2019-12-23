#include "../board/Board.hpp"
#include "../player/Player.hpp"

/**
 * Game class declaration
 */
class Game {
	private:
		Board* gameboard; // the current board
		Player* wh; Player* bl; // players
		int gameState; // CM, SM, C
		
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
		void setPlayerWhite(Player*);
		void setPlayerBlack(Player*);
		void setGameState(int);
	public:
		Game(Board*, Player*, Player*); // constructor
		
		// member methods
		void play();
};