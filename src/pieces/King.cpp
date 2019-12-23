#include "King.hpp"

/**
 * King class definition
 */

/**
 * King constructor
 * @param c - the color of the piece
 */
King::King(bool c) {
	setColor(c);
	setValue(100); // king is worth 100 points
	setType('K'); // method will convert to 'k' if needed
	setMoved(false);
}

/**
 * copy constructor
 * @return - a copy of this object
 */
std::auto_ptr<Piece> King::clone() const {
	return std::auto_ptr<Piece>(new King(*this));
}

/**
 * Movement method
 * creates a collection of valid moves the piece can make
 * @param b - the current board
 * @param c, r - the coordinate of the piece
 * @return - a collection of moves
 */
std::vector<Move> King::getMoves(Board* b, unsigned int c, unsigned int r) {
	std::vector<Move> moveList;
	/**
	 * king has a move in eight directions so find
	 * all possible moves and add to the list if possible
	 */
	for (unsigned int j = 0; j < MOVE_NUM; j++) {
		int x = c, y = r; // signed as it may be OOB later
		switch(j) {
			// functionality is essentially rook + bishop but length 1
			case 0: y += MIN_MOVE; break; // north
			case 1: x += MIN_MOVE; y += MIN_MOVE; break; // north-east
			case 2: x += MIN_MOVE; break; // east
			case 3: x += MIN_MOVE; y -= MIN_MOVE; break; // south-east
			case 4: y -= MIN_MOVE; break; // south
			case 5: x -= MIN_MOVE; y -= MIN_MOVE; break; // south-west
			case 6: x -= MIN_MOVE; break; // west
			case 7: x -= MIN_MOVE; y += MIN_MOVE; break; // north-west
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
	/**
	 * the below is castling specific code separated
	 * as it does not follow normal movement pattern
	 *
	 * verify that initial conditions met
	 * these are the only valid positions a king may castle
	 */
	bool checkWhitePos = (getColor() && c == 4 && r == 0);
	bool checkBlackPos = (!getColor() && c == 4 && r == 7);
	if (!getMoved() && (checkWhitePos || checkBlackPos)) { // if first move
		// two directions to castle
		for (unsigned int j = 0; j < 2; j++) {
			/**
			 * castling to the east requires a check of
			 * two positions between king and rook, whereas
			 * castling to the west needs three position checks
			 */
			for (unsigned int i = 1; i < ((j == 0) ? 4 : 5); ++i) {
				// get prospective piece
				Tile castlePath = (*b)(((j == 0) ? c+i : c-i), r);
				// if path is not occupied but not at edge tile
				if (!castlePath) {
					// continue as not edge tile
					continue;
				// if occupied but not edge
				} else if (i < ((j == 0) ? 3 : 4)) {
					// there is some obstruction, so break
					break;
				}
				// check if matching color
				if (castlePath.getPiece().getColor() == getColor()) {
					// check if rook
					if (castlePath.getPiece().getType() == ((getColor()) ? 'R' : 'r')) {
						// only if the rook also has not moved
						if (!castlePath.getPiece().getMoved()) {
							// if unmoved rook of same color, valid castle
							moveList.push_back(Move(c, r, (j == 0) ? c+i : c-i, r));
						}
					}
				}
			}
		}
	}
	// remove moves that would otherwise put king into check
	removeIllegalMoves(b, moveList);
	return moveList;
}

/**
 * method to remove moves that would be illegal
 * @param b - the board the piece is on
 */
void King::removeIllegalMoves(Board* b, std::vector<Move> &m) {
	std::vector<int> indexes; // so the indices don't get clobbered
	// find all moves an opponent could make
	std::vector<Move> moveList = b->getAllNonKingMoves(getColor());
	for (unsigned int i = 0; i < m.size(); i++) {
		for (unsigned int j = 0; j < moveList.size(); j++) {
			/**
			 * if move would result in being in way of another piece
			 * or if move would bring king next to king
			 * or if move would result in check
			 */
			if (m[i] >= moveList[j]) {
				indexes.insert(indexes.begin(), i);
				break;
			}
		}
	}
	// remove the moves that would put king in check
	for (unsigned int i = 0; i < indexes.size(); i++) {
		m.erase(m.begin() + indexes[i]);
	}
	// reset indices, need new set for paths
	indexes.clear();
	/**
	 * remove move in which a path will coincide from opponent
	 * consider a scenario where you have - K - - R
	 * a king could not move west as it is still in the "killpath" of rook
	 */
	std::vector<Move> pathList = b->getAllPaths(getColor());
	for (unsigned int i = 0; i < m.size(); i++) {
		for (unsigned int j = 0; j < pathList.size(); j++) {
			// if destination of opponent path is within king move list
			if (m[i] >= pathList[j]) { indexes.insert(indexes.begin(), i); break; }
		}
	}
	// remove the moves that would put king in check
	for (unsigned int i = 0; i < indexes.size(); i++) {
		m.erase(m.begin() + indexes[i]);
	}
	indexes.clear();
	for (unsigned int i = 0; i < m.size(); i++) {
		if (checkSurroundingKings(b, m[i])) {
			indexes.insert(indexes.begin(), i);
		}
	}
	for (unsigned int i = 0; i < indexes.size(); i++) {
		m.erase(m.begin() + indexes[i]);
	}
	indexes.clear();
}

/**
 * method to check if a move is next to opposing king
 * @param b - the board to use
 * @param c, r - the coordinate to check
 * @return - whether that move has surrounding kings
 */
bool King::checkSurroundingKings(Board* b, Move m) {
	for (unsigned int i = 0; i < MOVE_NUM; i++) {
		int x = m.getDestC(), y = m.getDestR();
		switch(i) {
			// functionality is essentially rook + bishop but length 1
			case 0: y += MIN_MOVE; break; // north
			case 1: x += MIN_MOVE; y += MIN_MOVE; break; // north-east
			case 2: x += MIN_MOVE; break; // east
			case 3: x += MIN_MOVE; y -= MIN_MOVE; break; // south-east
			case 4: y -= MIN_MOVE; break; // south
			case 5: x -= MIN_MOVE; y -= MIN_MOVE; break; // south-west
			case 6: x -= MIN_MOVE; break; // west
			case 7: x -= MIN_MOVE; y += MIN_MOVE; break; // north-west
		}
		// check if move is in bounds, has a piece, and piece is opposing king
		if (checkInBounds(x, y) && (*b)(x, y) && (*b)(x, y).getPiece().getColor() != getColor()) {
			char king = (*b)(x, y).getPiece().getType();
			if (king == 'k' || king == 'K') {
				return true; // the move would bring king next to king = illegal
			}
		}
	}
	return false; // no surrounding kings
}