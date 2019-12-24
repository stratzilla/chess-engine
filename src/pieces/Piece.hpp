#pragma once
#include "../game/Move.hpp"
#include <vector>
#include <memory> // for shared_ptr

class Board; // forward declaration

/**
 * Piece class declaration
 * base class for derived pieces
 */
class Piece {
	protected:
		Piece(bool, unsigned int, char); // constructor
		
		// to avoid magic numbers: contain number of rows/cols
		const static unsigned int ROWS = 8, COLS = 8;
		const static bool WHITE = true, BLACK = false;		
		bool hasMoved; // whether piece has moved or not (K, R)		
		bool color; // the color of the piece
		unsigned int value; // the value of the piece
		char type; // what kind of piece it is
		
		// protected member methods
		bool checkInBounds(unsigned int, unsigned int);
	public:
		virtual ~Piece(); // destructor	
		// pure abstract copy constructor
		virtual std::shared_ptr<Piece> clone() const=0;
		
		// public member methods
		virtual std::vector<Move> getMoves(Board*, unsigned int, unsigned int) = 0;
		
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