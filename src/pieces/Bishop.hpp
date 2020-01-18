#pragma once
#include "Piece.hpp"
#include "../board/Board.hpp"

// Bishop class declaration, derived class from base Piece class

class Bishop : public Piece {
	private:
		// the number of directions or moves
		const static unsigned int MOVE_NUM = 4;
		// the least it may move
		const static unsigned int MIN_MOVE = 1;
		// the furthest it may move
		const static unsigned int MAX_MOVE = 8;
	public:
		Bishop(bool); // constructor
		std::shared_ptr<Piece> clone() const; // copy constructor

		// member methods
		std::vector<Move> getMoves(Board*, unsigned int, unsigned int);
};
