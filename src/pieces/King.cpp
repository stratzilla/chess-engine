#include "King.hpp"

// King class definition, defines the behavior of King pieces

/**
 * King constructor
 * @param c - the color of the piece
 */
King::King(bool c)
	: Piece(c, GameParams::K_VAL, 'K') {} // chain into base constructor

/**
 * explicit copy constructor
 * @return - a copy of this object
 */
std::shared_ptr<Piece> King::clone() const {
	return std::shared_ptr<Piece>(new King(*this));
}

/**
 * method to determine which moves this piece may make, creates a collection of
 * valid moves the piece can make
 * @param b - the board the piece is on
 * @param c - the columnar coordinate of the piece
 * @param r - the row coordinate of the piece
 * @return - a collection of moves this piece may make
 */
std::vector<Move> King::getMoves(Board* b, unsigned int c, unsigned int r) {
	std::vector<Move> moveList;
	for (unsigned int j = 0; j < MOVE_NUM; j++) {
		int x = c, y = r; // signed as it may be OOB later
		switch(j) {
			case 0: y += MIN_MOVE; break; // north
			case 1: x += MIN_MOVE; y += MIN_MOVE; break; // north-east
			case 2: x += MIN_MOVE; break; // east
			case 3: x += MIN_MOVE; y -= MIN_MOVE; break; // south-east
			case 4: y -= MIN_MOVE; break; // south
			case 5: x -= MIN_MOVE; y -= MIN_MOVE; break; // south-west
			case 6: x -= MIN_MOVE; break; // west
			case 7: x -= MIN_MOVE; y += MIN_MOVE; break; // north-west
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
			} else { // if tile is not occupied
				// by default, a non-occupied tile is a valid move
				moveList.push_back(Move(c, r, x, y));
			}
		}
	}
	/**
	 * castling specific code separated as it does not follow normal movement
	 * pattern
	 */
	bool checkWhitePos = (getColor() && c == 4 && r == 0); // valid W pos
	bool checkBlackPos = (!getColor() && c == 4 && r == 7); // valid B pos
	if (!getMoved() && (checkWhitePos || checkBlackPos)) { // if first move
		for (unsigned int j = 0; j < CASTLE_MOVE; j++) {
			/**
			 * castling to the east requires a check of two positions between
			 * king and rook, whereas castling to the west needs three position
			 * checks
			 */
			for (unsigned int i = 1; i < ((j == 0) ? 4 : 5); ++i) {
				Tile castle = (*b)(((j == 0) ? c+i : c-i), r);
				// if path is not occupied but not at edge
				if (!castle) {
					continue; // continue as not edge tile
				// if occupied but not at edge
				} else if (i < ((j == 0) ? 3 : 4)) {
					break; // there is some obstruction, castling not possible
				}
				// check if matching color
				if (castle.getPiece().getColor() == getColor()) {
					// check if rook
					if (castle.getPiece().getValue() == GameParams::R_VAL) {
						// only if the rook also has not moved
						if (!castle.getPiece().getMoved()) {
							// if unmoved rook of same color, valid castle
							Move castleMove(c, r, (j == 0) ? c+i : c-i, r);
							moveList.push_back(castleMove);
						}
					}
				}
			}
		}
	}
	// remove invalid moves
	removeSurroundingKings(b, moveList);
	removeCheckedMoves(b, moveList);
	return moveList;
}

/**
 * method to remove moves which put king next to king
 * @param b - the board the king is on
 * @param m - movelist to remove from
 */
inline void King::removeSurroundingKings(Board* b, std::vector<Move> &m) {
	std::vector<int> indexes;
	for (unsigned int j = 0; j < m.size(); j++) {
		for (unsigned int i = 0; i < MOVE_NUM; i++) {
			int x = m[j].getDestC(), y = m[j].getDestR();
			switch(i) {
				case 0: y += MIN_MOVE; break; // north
				case 1: x += MIN_MOVE; y += MIN_MOVE; break; // north-east
				case 2: x += MIN_MOVE; break; // east
				case 3: x += MIN_MOVE; y -= MIN_MOVE; break; // south-east
				case 4: y -= MIN_MOVE; break; // south
				case 5: x -= MIN_MOVE; y -= MIN_MOVE; break; // south-west
				case 6: x -= MIN_MOVE; break; // west
				case 7: x -= MIN_MOVE; y += MIN_MOVE; break; // north-west
			}
			// check if move is in bounds and has a piece
			if (checkInBounds(x, y) && (*b)(x, y)) {
				// if occupying piece is opposing color
				if ((*b)(x, y).getPiece().getColor() != getColor()) {
					// if piece is king
					if ((*b)(x, y).getPiece().getValue() == GameParams::K_VAL) {
						indexes.insert(indexes.begin(), j);
					}
				}
			}
		}
	}
	for (unsigned int i = 0; i < indexes.size(); i++) {
		m.erase(m.begin() + indexes[i]);
	}
	indexes.clear();
}

/**
 * method to remove moves which would put king in check
 * @param b - the board the king is on
 * @param m - movelist to remove moves from
 */
inline void King::removeCheckedMoves(Board* b, std::vector<Move> &m) {
	std::vector<int> indexes;
	for (unsigned int i = 0; i < m.size(); i++) {
		// make move on a copy and check if in check
		Board* copy = new Board(*b);
		copy->movePiece(m[i]);
		if (copy->determineCheck(getColor())) {
			indexes.insert(indexes.begin(), i);
		}
		delete copy; // free up that memory
	}
	for (unsigned int i = 0; i < indexes.size(); i++) {
		m.erase(m.begin() + indexes[i]);
	}
	indexes.clear();
}
