#include "Human.hpp"

// Human class definition, defines behavior of the human controller player

/**
 * Human class constructor
 * @param c - the color of the player
 */
Human::Human(bool c) {
	setColor(c);
}

/**
 * method to prompt user for their move
 * @return - the move they've chosen
 */
Move Human::promptMove() {
	std::string s;
	// get all available moves
	std::vector<Move> moveList = getBoard()->getAllMoves(!getColor());
	removeCheckedMoves(moveList);
	while(true) { // continue prompting until valid
		std::cout << "\n";
		std::cout << "Enter a move in the form of 'a1b2' (from a1 to b2).\n";
		std::cout << "Or 'a1' to see moves (moves piece on a1 could make).\n";
		std::cout << "Or \"quit\" to quit game.\n\n";
		std::cout << "Input: "; std::cin >> s;
		// if command length is invalid
		if (s.size() != 2 && s.size() != 4) { errorMessage(1); continue; }
		// if quitting game
		if (s == "quit") { quitGame(); }
		// if invalid coordinates
		if (!verifyInput(s)) { errorMessage(2); continue; }
		// if no piece on origin tile
		if (!checkPiece(s[0]-97, s[1]-49)) { errorMessage(3); continue; }
		// if don't own tile
		if (!checkOwner(s[0]-97, s[1]-49)) { errorMessage(4); continue; }
		// if command of size 2, show moves
		if (s.size() == 2) {
			getBoard()->showMoves(s[0]-97, s[1]-49, moveList); continue;
		}
		// verify move is legal
		Move m(s[0]-97, s[1]-49, s[2]-97, s[3]-49);
		if (!verifyMove(m, moveList)) { errorMessage(5); continue; }
		// if it gets here, the move is valid, so make it
		break;
	}
	return Move(s[0]-97, s[1]-49, s[2]-97, s[3]-49);
}

/**
 * method to verify if a piece exists
 * @param c - the columnar coordinate of the piece
 * @param r - the row coordinate of the piece
 * @return - whether that piece exists
 */
inline bool Human::checkPiece(unsigned int c, unsigned int r) {
	return (*getBoard())(c, r);
}

/**
 * method to verify ownership of piece
 * @param c - the columnar coordinate of the piece
 * @param r - the row coordinate of the piece
 * @return - whether piece at coords belongs to user
 */
inline bool Human::checkOwner(unsigned int c, unsigned int r) {
	return getColor() == (*getBoard())(c, r).getPiece().getColor();
}

/**
 * method to verify the input is legal
 * @param s - the string input
 * @return - whether it's legal or not
 */
inline bool Human::verifyInput(std::string s) {
	// if origin column is valid
	if (s[0] < 97 || s[0] > 104) { return false; }
	// if origin row is valid
	if (s[1] < 49 || s[1] > 56) { return false; }
	if (s.size() == 4) { // for actual moves
		// if destination column is valid
		if (s[2] < 97 || s[2] > 104) { return false; }
		// if destination row is valid
		if (s[3] < 49 || s[3] > 56) { return false; }
	}
	return true;
}

/**
 * method to verify if move is legal
 * @param m - the proposed move
 * @param l - list of moves
 * @return - whether move is valid
 */
inline bool Human::verifyMove(Move m, std::vector<Move> l) {
	// verify the proposed move exists in the movelist
	for (unsigned int i = 0; i < l.size(); i++) {
		if (l[i] == m) { return true; }
	}
	return false;
}

/**
 * method to handle errors from invalid inputs
 * @param i - the type of error
 */
inline void Human::errorMessage(unsigned int i) {
	std::cout << "\n";
	switch(i) {
		case 1: std::cout << "This is not a valid input.\n"; break;
		case 2: std::cout << "This is not a valid move.\n"; break;
		case 3: std::cout << "There is no piece there.\n"; break;
		case 4: std::cout << "This piece is owned by the opponent.\n"; break;
		case 5: std::cout << "This is an illegal move.\n"; break;
	}
}

// method to handle game quitting
inline void Human::quitGame() {
	exit(0); // impossible to unwrap into main() unfortunately
}
