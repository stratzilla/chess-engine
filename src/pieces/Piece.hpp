#pragma once
#include "../game/Move.hpp"
#include <vector>
#include <memory> // for auto_ptr

class Board;

/**
 * Piece class declaration
 * base class for derived pieces
 */
class Piece {
	protected:
		// to avoid magic numbers: contain number of rows/cols
		const static unsigned int ROWS = 8, COLS = 8;
		
		bool hasMoved; // whether piece has moved or not (K, R)		
		bool color; // the color of the piece
		unsigned int value; // the value of the piece
		char type; // what kind of piece it is
		
		// protected member methods
		bool checkInBounds(unsigned int, unsigned int);
	public:
		virtual ~Piece(); // destructor	
		// pure abstract copy constructor
		virtual std::auto_ptr<Piece> clone() const=0;
	
		// likewise to avoid magic numbers: quantify which color is what
		const static bool WHITE = true, BLACK = false;
		
		// public member methods
		virtual std::vector<Move> getMoves(Board*, unsigned int, unsigned int);
		virtual std::vector<Move> getPaths(Board*, unsigned int, unsigned int);
		
		// accessor methods
		bool getMoved();
		bool getColor();
		unsigned int getValue();
		char getType();
		
		// mutator methods
		void setMoved(bool);
		void setColor(bool);
		void setValue(unsigned int);
		void setType(char);
};