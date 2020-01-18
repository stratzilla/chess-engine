#include "Game.hpp"

// Game class definition

/**
 * Game class constructor
 * @param b - the game board to use
 * @param white - the white player
 * @param black - the black player
 */
Game::Game(Board* b, Player* white, Player* black)
	: gameboard(b), playerA(white), playerB(black), gameState(0) {
	getPlayerWhite().setBoard(b); // allow visibility of board to white
	getPlayerBlack().setBoard(b); // same for black
}

// main game playing method
void Game::play() {
	while(true) { // continue playing while game not over
		// white move
		getBoard()->printBoard(); // print current board
		// check if checkmate, check, draw, or stalemate occurred
		if (getBoard()->determineCheckmate(getPlayerWhite().getColor())) {
			setGameState(3); break;
		}
		if (getBoard()->determineDraw()) { setGameState(2); break; }
		if (getBoard()->determineStalemate(getPlayerWhite().getColor())) {
			setGameState(1); break;
		}
		if (getBoard()->determineCheck(getPlayerWhite().getColor())) {
			std::cout << "\nWhite is in check!\n";
		}
		whiteMove(); // otherwise make a move
		// black move
		getBoard()->printBoard();
		if (getBoard()->determineCheckmate(getPlayerBlack().getColor())) {
			setGameState(4); break;
		}
		if (getBoard()->determineStalemate(getPlayerBlack().getColor())) {
			setGameState(1); break;
		}
		if (getBoard()->determineDraw()) { setGameState(2); break; }
		if (getBoard()->determineCheck(getPlayerBlack().getColor())) {
			std::cout << "\nBlack is in check!\n";
		}
		blackMove();
	}
	switch(getGameState()) { // if game is over
		case 1: std::cout << "\nStalemate.\n\n"; break;
		case 2: std::cout << "\nDraw.\n\n"; break;
		case 3: std::cout << "\nBlack checkmates white.\n\n"; break;
		case 4: std::cout << "\nWhite checkmates black.\n\n"; break;
	}
}

// white move function
inline void Game::whiteMove() {
	std::cout << "\nTurn " << moveCount << ", White to move...\n";
	// get a move as prompted
	Move m = getPlayerWhite().promptMove();
	std::cout << "\nWhite has moved " << m << "\n";
	makeMove(m); // make the move
	moveCount++;
}

// black move function
inline void Game::blackMove() {
	std::cout << "\nTurn " << moveCount << ", Black to move...\n";
	// get a move as prompted or AI generated
	Move m = getPlayerBlack().promptMove();
	std::cout << "\nBlack has moved " << m << "\n";
	makeMove(m); // make the move
	moveCount++;
}

/**
 * method to make the prompted move
 * @param m - the move to make
 */
inline void Game::makeMove(Move m) {
	getBoard()->movePiece(m);
}

// accessor methods
Board* Game::getBoard() { return gameboard; }
int Game::getGameState() { return gameState; }
Player& Game::getPlayerWhite() { return *playerA; }
Player& Game::getPlayerBlack() { return *playerB; }

// mutator methods
void Game::setGameState(int s) { gameState = s; }
