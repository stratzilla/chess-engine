#pragma once
#include "Tile.hpp"
#include "../pieces/Knight.hpp"
#include "../pieces/Bishop.hpp"
#include "../pieces/Rook.hpp"
#include "../pieces/Queen.hpp"
#include "../pieces/King.hpp"
#include "../pieces/Pawn.hpp"
#include <fstream>

/**
 * Board class declaration
 */
class Board {
	private:
		Tile tiles[8][8]; // how the board is organized		
		bool currentPlayer;
		
		// for readability
		const static bool WHITE = true, BLACK = false;
		const static unsigned int A=0, B=1, C=2, D=3, E=4, F=5, G=6, H=7;
		const static unsigned int COLS = 8, ROWS = 8;
		
		// private member methods
		void initNormalBoard();
		void initSavedBoard(std::string);
	public:
		Board(); // default constructor
		Board(std::string); // parameterized constructor
		
		// public member methods
		void printBoard();
		void showMoves(unsigned int, unsigned int, std::vector<Move>);
		void movePiece(Move);
		void saveToFile(std::string, bool);
		std::vector<Move> getAllMoves(bool);
		std::vector<Move> getAllNonKingMoves(bool);
		bool determineCheckmate(bool);
		bool determineStalemate(bool);
		bool determineCheck(bool);
		int getAllPieceValues(bool);
		int getAllMobilityValues(bool);
		int getAllPawnValues(bool);
		
		// accessor methods
		bool getCurrentPlayer();
		
		// mutator methods
		void setCurrentPlayer(bool);
		
		// operator methods
		Tile& operator()(unsigned int, unsigned int);
		Tile const& operator()(unsigned int, unsigned int) const;
};