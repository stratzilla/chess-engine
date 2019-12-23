#include "Knight.hpp"

/**
 * Knight class definition
 */

/**
 * Knight constructor
 * @param c - the color of the piece
 */
Knight::Knight(bool c) {
	setColor(c);
	setValue(3); // knight is worth 3 points
	setType('N'); // method will convert to 'n' if needed
	setMoved(false);
}

/**
 * copy constructor
 * @return - a copy of this object
 */
std::auto_ptr<Piece> Knight::clone() const {
	return std::auto_ptr<Piece>(new Knight(*this));
}

/**
 * Movement method
 * creates a collection of valid moves the piece can make
 * @param b - the current board
 * @param c, r - the coordinate of the piece
 * @return - a collection of moves
 */
std::vector<Move> Knight::getMoves(Board* b, unsigned int c, unsigned int r) {
	std::vector<Move> moveList;
	/**
	 * knight has at most eight possible moves at any time
	 * so add these moves if possible to the movelist
	 */
	for (unsigned int i = 0; i < MOVE_NUM; i++) {
		int x = c, y = r; // signed as it may be OOB later
		switch(i) {
			case 0: x += MIN_MOVE; y += MAX_MOVE; break; // north-north-east
			case 1: x -= MIN_MOVE; y += MAX_MOVE; break; // north-north-west
			case 2: x += MAX_MOVE; y += MIN_MOVE; break; // east-north-east
			case 3: x += MAX_MOVE; y -= MIN_MOVE; break; // east-south-east
			case 4: x -= MAX_MOVE; y += MIN_MOVE; break; // west-north-west
			case 5: x -= MAX_MOVE; y -= MIN_MOVE; break; // west-south-west
			case 6: x += MIN_MOVE; y -= MAX_MOVE; break; // south-south-east
			case 7: x -= MIN_MOVE; y -= MAX_MOVE; break; // south-south-west
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
			} else { // if not occupied
				// by default it is a valid move
				moveList.push_back(Move(c, r, x, y));
			}
		}
	}
	return moveList;
}