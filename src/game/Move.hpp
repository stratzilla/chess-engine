#pragma once
#include <sstream>

// Move class declaration

class Move {
	private:
		unsigned int origC, origR; // origin of move
		unsigned int destC, destR; // destination of move
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

		// operator methods
		bool operator==(Move&);
		bool operator>=(Move&);
		bool operator<=(Move&);
		friend std::ostream& operator<<(std::ostream&, Move&);
};
