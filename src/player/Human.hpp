#include "Player.hpp"

// Human class declaration, derived class from base Player class

class Human : public Player {
	private:
		// private member methods
		void errorMessage(unsigned int);
		bool verifyInput(std::string);
		bool verifyShow(std::string);
		bool verifyMove(Move, std::vector<Move>);
		bool checkOwner(unsigned int, unsigned int);
		bool checkPiece(unsigned int, unsigned int);
		void quitGame();
	public:
		Human(bool); // constructor

		// public member methods
		Move promptMove();
};
