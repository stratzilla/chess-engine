#include "Piece.hpp"

/**
 * Piece class definition
 */

/**
 * piece class constructor
 * @param c - the color of the piece
 * @param v - the value of the piece
 * @param t - the type of the piece
 */
Piece::Piece(bool c, unsigned int v, char t)
	: color(c), value(v), hasMoved(false) {
		setType(t);
}

// virtual destructor
Piece::~Piece() {}

/**
 * method to confirm a move is valid (within bounds)
 * @param c - the columnar coordinate of the move
 * @param r - the row coordinate of the move
 * @return - whether the move is within the board
 */
bool Piece::checkInBounds(unsigned int c, unsigned int r) {
	return (r < ROWS) && (c < COLS);
}

// accessor methods
bool Piece::getMoved() { return hasMoved; }
bool Piece::getColor() { return color; }
unsigned int Piece::getValue() { return value; }
char Piece::getType() { return type; }

// mutator methods
void Piece::setMoved(bool m) { hasMoved = m; }
inline void Piece::setType(char t) { type = (getColor() == 1) ? t : t + 32; }
