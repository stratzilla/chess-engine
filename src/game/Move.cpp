#include "Move.hpp"

// Move class definition, defines how moves are encapsulated and accessed

// Move default constructor
Move::Move() {}

/**
 * Move parameterized constructor
 * @param oC, oR - the origin of the move (col, row)
 * @param dC, dR - the destination of the move (col, row)
 */
Move::Move(unsigned int oC, unsigned int oR, unsigned int dC, unsigned int dR)
	: origC(oC), origR(oR), destC(dC), destR(dR) {}

/**
 * method to create printable string of move
 * @return - the move concatenated to a string
 */
std::string Move::stateMove() {
	// this is for standard chess notation
	std::stringstream toReturn;
	toReturn << (char)(origC+97) << (char)(origR+49); // origin
	toReturn << (char)(destC+97) << (char)(destR+49); // destination
	return toReturn.str();
}

// accessor methods
unsigned int Move::getOrigR() { return origR; }
unsigned int Move::getOrigC() { return origC; }
unsigned int Move::getDestR() { return destR; }
unsigned int Move::getDestC() { return destC; }

// operator methods
bool Move::operator==(Move &m) {
	// determine if origin and destination are equivalent
	bool sameOrig = (getOrigR() == m.getOrigR() && getOrigC() == m.getOrigC());
	bool sameDest = (getDestR() == m.getDestR() && getDestC() == m.getDestC());
	return sameOrig && sameDest;
}

bool Move::operator<=(Move &m) {
	// determine if origin is equivalent
	return (getOrigR() == m.getOrigR() && getOrigC() == m.getOrigC());
}

bool Move::operator>=(Move &m) {
	// determine if destination is equivalent
	return (getDestR() == m.getDestR() && getDestC() == m.getDestC());
}

std::ostream& operator<<(std::ostream &out, Move &m) {
	out << m.stateMove();
	return out;
}