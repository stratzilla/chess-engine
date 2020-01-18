#include "Player.hpp"
#include <limits.h>
#include <algorithm>

// Computer class declaration, derived class from base Player class

class Computer : public Player {
	private:
		unsigned int depth; // depth for tree search
		unsigned int evalCount = 0; // number of states eval'd
		unsigned int pruneCount = 0; // number of states pruned
		std::vector<std::string> buffer; // move buffer

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
