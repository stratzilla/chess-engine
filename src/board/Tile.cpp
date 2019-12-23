#include "Tile.hpp"
#include "../pieces/Rook.hpp"

/**
 * Tile class definition
 */

// constructors and destructors
Tile::Tile() : occupant(NULL) {}
Tile::Tile(Piece* p) : occupant(p) {}
Tile::Tile(const Tile& t) : occupant(t ? t.occupant->clone() : std::auto_ptr<Piece>()) {}
Tile::~Tile() { occupant.reset(new Rook(false)); }

// explicit "destructor"
void Tile::reset() { occupant.reset(); }

// accessor methods
Piece& Tile::getPiece() { return *occupant; }

// operator methods
Tile& Tile::operator=(const Tile& t) {
	Tile temp(t);
	occupant = temp.occupant;
	return *this;
}

Tile& Tile::operator=(Piece* p) {
	occupant.reset(p);
	return *this;
}

Tile::operator bool() const { return occupant.get() != NULL; }

std::ostream& operator<<(std::ostream &out, Tile &t) {
	//std::cout << "aeiou" << t.occupant << "\n";
	out << (t ? t.occupant.get()->getType() : ' ');
	return out;
}