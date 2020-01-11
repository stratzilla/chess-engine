#include "Pawn.hpp"

// Pawn class definition, defines the behavior of Pawn pieces

/**
 * Pawn constructor
 * @param c - the color of the piece
 */
Pawn::Pawn(bool c)
	: Piece(c, GameParams::P_VAL, 'P') {} // chain into base constructor

/**
 * explicit copy constructor
 * @return - a copy of this object
 */
std::shared_ptr<Piece> Pawn::clone() const {
	return std::shared_ptr<Piece>(new Pawn(*this));
}

/**
 * method to determine which moves this piece may make, creates a collection of
 * valid moves the piece can make
 * @param b - the board the piece is on
 * @param c - the columnar coordinate of the piece
 * @param r - the row coordinate of the piece
 * @return - a collection of moves this piece may make
 */
std::vector<Move> Pawn::getMoves(Board* b, unsigned int c, unsigned int r) {
	std::vector<Move> moveList;
	// an offset is needed: white moves north, black moves south
	int offset = (getColor() == WHITE) ? 1 : -1;
	for (unsigned int i = 0; i < MOVE_NUM; i++) {
		// moving two spaces is only available for a pawn's first move
		if (i == 1 && getMoved()) { continue; }
		int x = c, y = r; // signed as it may be OOB later
		switch(i) {
			case 0: y += (MIN_MOVE * offset); break; // one space
			case 1: y += (MAX_MOVE * offset); break; // two spaces
			case 2: y += (MIN_MOVE * offset); x += MIN_MOVE; break; // R. diag
			case 3: y += (MIN_MOVE * offset); x -= MIN_MOVE; break; // L. diag
		}
		// determine if the move is valid
		if (checkInBounds(x, y)) { // if valid board position
			// cannot capture going forward
			if ((i == 0 || i == 1) && (*b)(x, y)) { continue; }
			// cannot jump over pieces
			if (i == 1 && (*b)(x, y - (MIN_MOVE * offset))) {
				continue;
			}
			Tile possibleMove = (*b)(x, y);
			if ((i == 2 || i == 3) && possibleMove) { // if tile is occupied
				// if occupying piece is opposing color
				if (possibleMove.getPiece().getColor() != color) {
					// capturing the piece is a valid move
					moveList.push_back(Move(c, r, x, y));
				}
			} else if (!(i == 2 || i == 3)) { // if tile is not occupied
				// by default, a non-occupied tile is a valid move
				moveList.push_back(Move(c, r, x, y));
			}
		}
	}
	return moveList;
}