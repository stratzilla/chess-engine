#pragma once
#include "Piece.hpp"
#include "../board/Board.hpp"

// Queen class declaration, derived class from base Piece class

class Queen : public Piece {
	private:
		// the number of directions or moves
		const static unsigned int MOVE_NUM = 8;
		// the least it may move
		const static unsigned int MIN_MOVE = 1;
		// the furthest it may move
		const static unsigned int MAX_MOVE = 8;
	public:
		Queen(bool); // constructor
		std::shared_ptr<Piece> clone() const; // copy constructor

		// member methods
		std::vector<Move> getMoves(Board*, unsigned int, unsigned int);
};
