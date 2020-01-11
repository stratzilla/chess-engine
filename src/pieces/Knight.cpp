#include "Knight.hpp"

// Knight class definition, defines the behavior of Knight pieces

/**
 * Knight constructor
 * @param c - the color of the piece
 */
Knight::Knight(bool c)
	: Piece(c, GameParams::N_VAL, 'N') {} // chain into base constructor

/**
 * explicit copy constructor
 * @return - a copy of this object
 */
std::shared_ptr<Piece> Knight::clone() const {
	return std::shared_ptr<Piece>(new Knight(*this));
}

/**
 * method to determine which moves this piece may make, creates a collection of
 * valid moves the piece can make
 * @param b - the board the piece is on
 * @param c - the columnar coordinate of the piece
 * @param r - the row coordinate of the piece
 * @return - a collection of moves this piece may make
 */
std::vector<Move> Knight::getMoves(Board* b, unsigned int c, unsigned int r) {
	std::vector<Move> moveList;
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
		// determine if the move is valid
		if (checkInBounds(x, y)) { // if valid board position
			Tile possibleMove = (*b)(x, y);
			if (possibleMove) { // if tile is occupied
				// if occupying piece is opposing color
				if (possibleMove.getPiece().getColor() != color) {
					// capturing the piece is a valid move
					moveList.push_back(Move(c, r, x, y));
				}
			} else { // if tile not occupied
				// by default, a non-occupied tile is a valid move
				moveList.push_back(Move(c, r, x, y));
			}
		}
	}
	return moveList;
}