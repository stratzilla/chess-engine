#include "Bishop.hpp"

// Bishop class definition, defines the behavior of Bishop pieces

/**
 * Bishop constructor
 * @param c - the color of the piece
 */
Bishop::Bishop(bool c)
	: Piece(c, GameParams::B_VAL, 'B') {} // chain into base constructor

/**
 * explicit copy constructor
 * @return - a copy of this object
 */
std::shared_ptr<Piece> Bishop::clone() const {
	return std::shared_ptr<Piece>(new Bishop(*this));
}

/**
 * method to determine which moves this piece may make, creates a collection of
 * valid moves the piece can make
 * @param b - the board the piece is on
 * @param c - the columnar coordinate of the piece
 * @param r - the row coordinate of the piece
 * @return - a collection of moves this piece may make
 */
std::vector<Move> Bishop::getMoves(Board* b, unsigned int c, unsigned int r) {
	std::vector<Move> moveList;
	for (unsigned int j = 0; j < MOVE_NUM; j++) {
		int x = c, y = r; // signed as it may be OOB later
		for (unsigned int i = MIN_MOVE; i < MAX_MOVE; i++, x = c, y = r) {
			switch(j) {
				case 0: x += i; y += i; break; // north-east
				case 1: x += i; y -= i; break; // south-east
				case 2: x -= i; y -= i; break; // south-west
				case 3: x -= i; y += i; break; // north-west
			}
			// determine if the move is valid
			if (checkInBounds(x, y)) { // if valid board position
				Tile possibleMove = (*b)(x, y);
				if (possibleMove) { // if tile is occupied
					// if occupying piece is opposing color
					if (possibleMove.getPiece().getColor() != color) {
						// capturing the piece is a valid move
						moveList.push_back(Move(c, r, x, y));
					}
					break; // cannot go over pieces
				} else { // if tile is not occupied
					// by default, a non-occupied tile is a valid move
					moveList.push_back(Move(c, r, x, y));
				}
			} else {
				/**
				 * if a move is outside of bounds, it's reasonable to assume
				 * one move further in the same direction is also out of bounds
				 */
				break;
			}
		}
	}
	return moveList;
}