#pragma once
#include <sstream>
#include <iostream>
#include "../pieces/Piece.hpp"

/**
 * Tile class declaration
 */
class Tile {
	private:
		std::auto_ptr<Piece> occupant; // the occupying piece
	public:
		Tile(); // default constructor
		Tile(Piece* p); // parameterized constructor
		Tile(const Tile& t); // copy constructor
		~Tile(); // destructor
		
		// member methods
		void reset();
		
		// accessor methods
		Piece& getPiece();
		
		// operator methods
		Tile& operator=(const Tile&);
		Tile& operator=(Piece*);
		operator bool() const;
		friend std::ostream& operator<<(std::ostream&, Tile&); // stream insertion
};