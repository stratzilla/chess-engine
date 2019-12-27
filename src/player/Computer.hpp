#include "Player.hpp"
#include <limits.h>
#include <algorithm>

/**
 * Computer class declaration
 * derived class from base Player class
 */
class Computer : public Player {
	private:
		unsigned int depth;
		unsigned int evalCount;
		std::vector<std::string> buffer;
		
		// private member methods
		Move negamaxHandler(int, int);
		int negamax(Board*, unsigned int, int, int, bool);
		int evalBoard(Board*);
		void printData(int, unsigned int);
		
		// accessor methods
		unsigned int getDepth();
		
		// mutator methods
		void setDepth(unsigned int);
	public:
		Computer(bool, unsigned int);
		
		// public member methods
		Move promptMove();
};