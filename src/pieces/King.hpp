#pragma once
#include "Piece.hpp"
#include "../board/Board.hpp"

// King class declaration, derived class from base Piece class

class King : public Piece {
	private:
		// the number of directions or moves
		const static unsigned int MOVE_NUM = 8;
		// the least it may move
		const static unsigned int MIN_MOVE = 1;
		// the furthest it may move
		const static unsigned int MAX_MOVE = 1;
		// for castling moves
		const static unsigned int CASTLE_MOVE = 2;

		// private member methods
		void removeSurroundingKings(Board*, std::vector<Move>&);
		void removeCheckedMoves(Board*, std::vector<Move>&);
	public:
		King(bool); // constructor
		std::shared_ptr<Piece> clone() const; // copy constructor

		// public member methods
		std::vector<Move> getMoves(Board*, unsigned int, unsigned int);
};
