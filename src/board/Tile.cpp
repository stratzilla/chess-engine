#include "Tile.hpp"

// Tile class definition

// constructors and destructors
Tile::Tile() : occupant(NULL) {}
Tile::Tile(Piece* p) : occupant(p) {}
Tile::~Tile() { occupant.reset(); }
Tile::Tile(const Tile& t)
	: occupant(t ? t.occupant->clone() : std::shared_ptr<Piece>()) {}

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
	out << (t ? t.occupant.get()->getType() : ' ');
	return out;
}
