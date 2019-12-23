#include "Piece.hpp"

/**
 * Piece class definition
 */

// virtual destructor
Piece::~Piece() {}

/**
 * method to confirm a move is valid (within bounds)
 * @param r, c - the coordinate of the move
 * @return - whether the move is within the board
 */
bool Piece::checkInBounds(unsigned int c, unsigned int r) {
	// I'm confident an unsigned int cannot be less than zero :)
	return (r < ROWS) && (c < COLS); 
}

/**
 * method for getting moves
 * default behavior implicitly overriden by derived classes
 * in other words, never used
 */
std::vector<Move> Piece::getMoves(Board* b, unsigned int c, unsigned int r) {
	std::vector<Move> vec;
	return vec;
}

/**
 * method for getting paths
 * default behavior implicitly overriden by derived classes
 * in other words, never used
 */
std::vector<Move> Piece::getPaths(Board* b, unsigned int c, unsigned int r) {
	std::vector<Move> vec;
	return vec;
}

// accessor methods
bool Piece::getMoved() { return hasMoved; }
bool Piece::getColor() { return color; }
unsigned int Piece::getValue() { return value; }
char Piece::getType() { return type; }

// mutator methods
void Piece::setMoved(bool m) { hasMoved = m; }
void Piece::setColor(bool c) { color = c; }
void Piece::setValue(unsigned int v) { value = v; }
void Piece::setType(char t) { type = (getColor() == 1) ? t : t + 32; }