#pragma once
#include <string>
#include <sstream>

/**
 * Move class declaration
 */
class Move {
	private:
		unsigned int origR, origC; // origin of move
		unsigned int destR, destC; // destination of move
	public:
		Move(); // default constructor
		// parameterized constructor
		Move(unsigned int, unsigned int, unsigned int, unsigned int);
		
		// member methods
		std::string stateMove();
		
		// accessor methods
		unsigned int getOrigR();
		unsigned int getOrigC();
		unsigned int getDestR();
		unsigned int getDestC();
		
		// mutator methods
		void setOrigR(unsigned int);
		void setOrigC(unsigned int);
		void setDestR(unsigned int);
		void setDestc(unsigned int);
		
		// operator methods
		bool operator==(Move&);
		bool operator>=(Move&);
		bool operator<=(Move&);
		friend std::ostream& operator<<(std::ostream&, Move&);
};