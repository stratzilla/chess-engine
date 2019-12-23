#pragma once
#include "Piece.hpp"
#include "../board/Board.hpp"

/**
 * Pawn class declaration
 * derived class from base Piece class
 */
class Pawn : public Piece {
	private:
		// the number of directions or moves
		const static unsigned int MOVE_NUM = 4;
		// the least it may move
		const static unsigned int MIN_MOVE = 1;
		// the furthest it may move
		const static unsigned int MAX_MOVE = 2;
	public:
		Pawn(bool); // constructor		
		std::auto_ptr<Piece> clone() const; // copy constructor
		
		// member methods
		std::vector<Move> getMoves(Board*, unsigned int, unsigned int);
};