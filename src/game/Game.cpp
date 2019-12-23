#include "Game.hpp"
#include "../player/Player.hpp"

/**
 * Game class definition
 */

/**
 * Game class constructor
 * @param b - the game board to use
 * @param white - the white player
 * @param black - the black player
 */
Game::Game(Board* b, Player* white, Player* black) { 
	gameboard = b;
	setPlayerWhite(white);
	getPlayerWhite().setBoard(b); // allow visibility of board to white
	setPlayerBlack(black);
	getPlayerBlack().setBoard(b); // same for black
	// initially set to draw condition, doesn't mean draw until later
	setGameState(0);
}

// main game playing method
void Game::play() {
	while(true) { // continue playing while game not over
		// for custom boards, determine current player
		if (getBoard()->getCurrentPlayer()) {
			getBoard()->printBoard(); // print current board
			// check if checkmate, check, or stalemate occurred
			if (getBoard()->determineCheckmate(getPlayerWhite().getColor())) {
				setGameState(-1); break; 
			}
			if (getBoard()->determineStalemate(getPlayerWhite().getColor())) {
				break;
			}
			if (getBoard()->determineCheck(getPlayerWhite().getColor())) {
				std::cout << "\nWhite is in check!\n";
			}
			whiteMove(); // otherwise make a move
		} else if (!getBoard()->getCurrentPlayer()) {
			getBoard()->printBoard();
			if (getBoard()->determineCheckmate(getPlayerBlack().getColor())) { 
				setGameState(1); break;
			}
			if (getBoard()->determineStalemate(getPlayerBlack().getColor())) {
				break;
			}
			if (getBoard()->determineCheck(getPlayerBlack().getColor())) {
				std::cout << "\nBlack is in check!\n";
			}
			blackMove();
		}
		// alternate player
		getBoard()->setCurrentPlayer(!getBoard()->getCurrentPlayer());
	}
	switch(getGameState()) { // if game is over
		case -1: std::cout << "\nBlack checkmates white.\n\n"; break;
		case 0: std::cout << "\nStalemate.\n\n"; break;
		case 1: std::cout << "\nWhite checkmates black.\n\n"; break;
	}
}

// white move function
void Game::whiteMove() {
	std::cout << "\nWhite to move...\n";
	// get a move as prompted
	Move m = getPlayerWhite().promptMove(getPlayerWhite().getColor());
	std::cout << "\nWhite has moved " << m << "\n";
	makeMove(m); // make the move
}

// black move function
void Game::blackMove() {
	std::cout << "\nBlack to move...\n";
	// get a move as prompted or AI generated
	Move m = getPlayerBlack().promptMove(getPlayerBlack().getColor());
	std::cout << "\nBlack has moved " << m << "\n";
	makeMove(m); // make the move
}

/**
 * method to make the prompted move
 * @param m - the move to make
 */
void Game::makeMove(Move m) {
	getBoard()->movePiece(m);
}

// accessor methods
Board* Game::getBoard() { return gameboard; }
int Game::getGameState() { return gameState; }
Player& Game::getPlayerWhite() { return *wh; }
Player& Game::getPlayerBlack() { return *bl; }

// mutator methods
void Game::setPlayerWhite(Player* p) { wh = p; }
void Game::setPlayerBlack(Player* p) { bl = p; }
void Game::setGameState(int s) { gameState = s; }