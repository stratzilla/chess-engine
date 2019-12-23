#include "Pawn.hpp"

/**
 * Pawn class definition
 */

/**
 * Pawn constructor
 * @param c - the color of the piece
 */
Pawn::Pawn(bool c) {
	setColor(c);
	setValue(1); // pawn is worth 1 point
	setType('P'); // method will convert to 'p' if needed
	setMoved(false);
}

/**
 * copy constructor
 * @return - a copy of this object
 */
std::auto_ptr<Piece> Pawn::clone() const {
	return std::auto_ptr<Piece>(new Pawn(*this));
}

/**
 * Movement method
 * creates a collection of valid moves the piece can make
 * @param b - the current board
 * @param c, r - the coordinate of the piece
 * @return - a collection of moves
 */
std::vector<Move> Pawn::getMoves(Board* b, unsigned int c, unsigned int r) {
	std::vector<Move> moveList;
	/**
	 * an offset is needed depending on color:
	 * white moves north, black moves south
	 */
	int offset = (getColor() == WHITE) ? 1 : -1;
	/**
	 * pawn can move forward one (or two, if first move)
	 * and capture diagonally two ways
	 */
	for (unsigned int i = 0; i < MOVE_NUM; i++) {
		// moving two spaces is only available for a pawn's first move
		if (i == 1 && getMoved()) { continue; }
		int x = c, y = r; // signed as it may be OOB later
		switch(i) {
			case 0: y += (MIN_MOVE * offset); break; // one space
			case 1: y += (MAX_MOVE * offset); break; // two spaces
			case 2: y += (MIN_MOVE * offset); x += MIN_MOVE; break; // capture right diagonal
			case 3: y += (MIN_MOVE * offset); x -= MIN_MOVE; break; // capture left diagonal
		}
		// if they're a valid move, append to the movelist
		if (checkInBounds(x, y)) { // if valid board position
			// cannot capture going forward
			if ((i == 0 || i == 1) && (*b)(x, y)) { continue; }
			// if moving two spaces, you cannot jump over a piece
			if (i == 1 && (*b)(x, y - (MIN_MOVE * offset))) {
				continue;
			}
			Tile possibleMove = (*b)(x, y); // get the tile
			// if case where capture possible
			bool v = (i == 2 || i == 3);
			// check if open
			if (v && possibleMove) { // if occupied
				// if capturing piece
				if (possibleMove.getPiece().getColor() != color) {
					// valid move
					moveList.push_back(Move(c, r, x, y));
				}
			} else if (!v) { // if not occupied
				// by default it is a valid move
				moveList.push_back(Move(c, r, x, y));
			} // consider capturing cases, it is not valid even if unoccupied
		}
	}
	return moveList;
}