#include "Bishop.hpp"

/**
 * Bishop class definition
 */

/**
 * Bishop constructor
 * @param c - the color of the piece
 */
Bishop::Bishop(bool c)
	: Piece(c, 3, 'B') {}

/**
 * copy constructor
 * @return - a copy of this object
 */
std::shared_ptr<Piece> Bishop::clone() const {
	return std::shared_ptr<Piece>(new Bishop(*this));
}

/**
 * movement method
 * creates a collection of valid moves the piece can make
 * @param b - the current board
 * @param c, r - the coordinate of the piece
 * @return - a collection of moves
 */
std::vector<Move> Bishop::getMoves(Board* b, unsigned int c, unsigned int r) {
	std::vector<Move> moveList;
	/**
	 * bishop has multiple moves in four directions so find
	 * all possible moves and add to the list if possible
	 */
	for (unsigned int j = 0; j < MOVE_NUM; j++) {
		int x = c, y = r; // signed as it may be OOB later
		for (unsigned int i = MIN_MOVE; i < MAX_MOVE; i++, x = c, y = r) {
			switch(j) {
				case 0: x += i; y += i; break; // north-east
				case 1: x += i; y -= i; break; // south-east
				case 2: x -= i; y -= i; break; // south-west
				case 3: x -= i; y += i; break; // north-west
			}
			// if they're a valid move, append to the movelist
			if (checkInBounds(x, y)) { // if valid board position
				Tile possibleMove = (*b)(x, y); // get the tile
				if (possibleMove) { // if occupied
					// if capturing piece
					if (possibleMove.getPiece().getColor() != color) {
						// valid move
						moveList.push_back(Move(c, r, x, y));
					}
					break; // need to break because you can't go over pieces
				} else { // if not occupied
					// by default it is a valid move
					moveList.push_back(Move(c, r, x, y));
				}
			} else {
				/**
				 * if a move is outside of bounds, it's reasonable
				 * to assume one move further in the same direction
				 * is also out of bounds. Therefore we don't need to
				 * check further in that direction
				 */
				break;
			}
		}
	}
	return moveList;
}