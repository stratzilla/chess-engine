#include "Computer.hpp"

/**
 * Computer class definition
 */

/**
 * Computer class constructor
 * @param c - color of this player
 * @param d - the depth for AI tree search
 */
Computer::Computer(bool c, unsigned int d) {
	setColor(c);
	setDepth(d);
	evalCount = 0;
}

/**
 * method to prompt user for their move
 * @return - the move they've chosen
 */
Move Computer::promptMove() {
	// perform AI routine
	return negamaxHandler(); // as found by negamax
}

/**
 * negamax handler
 * since negamax deals with integers, we need
 * a way to devise a move with the highest value
 * as provided by negamax. This method effectively
 * takes care of the first sequential board state
 * and the inner negamax method deals with beyond
 * @return - AI determined best move
 */
Move Computer::negamaxHandler() {
	// get all moves you can make
	std::vector<Move> moveList = getBoard()->getAllMoves(!getColor());
	// remove moves which would put you in check
	removeCheckedMoves(moveList);
	int bestMoveValue = INT_MIN; // initially -inf
	std::vector<Move> bestMoves; // collection of best moves
	// for each possible move
	for (unsigned int i = 0; i < moveList.size(); i++) {
		/**
		 * to avoid threefold repetition, we need to handle cases
		 * where a move is repeated. Mostly evident in AI vs AI games
		 * where it will go on forever as they move pieces back
		 * and forth ad infinitum. This prevents reuse of the previous moves
		 * the amount of which is determined by a buffer. Added benefits
		 * of less negamax calls meaning faster speed
		 */
		if (std::find(moveQueue.begin(), moveQueue.end(), moveList[i].stateMove()) != moveQueue.end()) {
			continue;
		}
		Board* copy = new Board(*getBoard()); // make a new board copy
		copy->movePiece(moveList[i]); // make move on copy
		// find value of that move
		int value = -negamax(copy, getDepth()-1, INT_MIN, INT_MAX, !getColor());
		delete copy;
		// if same worth or not enough to fill queue
		if (value == bestMoveValue || moveList.size() <= BUFFER) {
			// add it to the collection
			bestMoves.push_back(moveList[i]);
		} else if (value > bestMoveValue) {
			// add it to the list of possible moves and update best score
			bestMoveValue = value;
			bestMoves.clear(); // don't need worse moves
			bestMoves.push_back(moveList[i]);
		}
	}
	/** 
	 * I was unable to catch instances where the movelist is zero, leading to null move
	 * so consider this the AI forfeiting
	 */
	if (bestMoves.size() == 0) {
		std::cout << (getColor() ? "White" : "Black") << " has forfeited the game.\n\n";
		exit(1);
	}
	/**
	 * because some moves will be worth the same as others, we'll have
	 * a collection of the best moves here. We'll choose one stochastically
	 */
	Move theBestMove = bestMoves[rand() % bestMoves.size()];
	moveQueue.push_back(theBestMove.stateMove()); // add best move to buffer
	// keep buffer size consistent
	if (moveQueue.size() > BUFFER) { moveQueue.erase(moveQueue.begin()); }
	printData(bestMoveValue, bestMoves.size()); // show some data
	return theBestMove;
}

/**
 * negamax implementation using alpha-beta pruning
 * will search tree space recursively but without
 * the typical two function calls that minimax uses
 * negamax relies on the property of:
 * max(alf, bet) == -min(-alf, -bet)
 * which is equivalent or better than vanilla minimax
 * @param b - the board to checkmate
 * @param d - the depth to use to break out of algorithm
 * @param alf - alpha
 * @param bet - beta
 * @param p - the calling player
 * @return - best evaluation for AI
 */
int Computer::negamax(Board* b, unsigned int d, int alf, int bet, bool p) {
	evalCount++; // increment count to display positions evaluated
	// terminal case would be stalemate or checkmate or depth zero
	if (d == 0) { // base recursive case
		/**
		 * consider a checkmate as best possible configuration
		 * this will become -INT_MAX were it the minimizing
		 * player, so it handles both cases
		 */
		if (b->determineCheckmate(p)) { return INT_MAX; }
		// consider a stalemate is better than losing
		if (b->determineStalemate(p)) { return 0; }
		return (p == getColor() ? 1 : -1) * evalBoard(b); // return that board's evaluation
	}
	// putting another person in check is beneficial
	if (b->determineCheck(p)) { return (p == getColor() ? 2 : -2) * evalBoard(b); }
	int value = INT_MIN; // initially minimum (will overwrite)
	std::vector<Move> moveList = b->getAllMoves(!p); // get moves of opponent
	for (unsigned int i = 0; i < moveList.size(); i++) {
		Board* copy = new Board(*b); // make a new board copy
		copy->movePiece(moveList[i]); // make move on copy
		// then recurse
		int v = -negamax(copy, d-1, -bet, -alf, !p);
		delete copy;
		value = std::max(value, v);
		alf = std::max(alf, value);
		if (alf >= bet) { break; } // cutoff for branches
	}
	return value;
}

/**
 * method to evaluate a board's worth
 * @param b - the board to evaluate
 * @return - total mobility according to AI
 */
int Computer::evalBoard(Board* b) {
	/**
	 * board evaluation is done in three steps:
	 *  1. find the values of all pieces
	 *  2. find the mobility of all pieces
	 *  3. find the pawn control
	 * then evaluation considers the total board
	 * value plus the board control plus pawn control
	 */
	int value = b->getAllPieceValues(getColor());
	int mobility = b->getAllMobilityValues(getColor()); // board control
	int pawns = b->getAllPawnValues(getColor()); // pawn control
	/**
	 * some coefficients to balance the weights
	 * of the various metrics about the board
	 */
	int c1 = 12, c2 = 1, c3 = 3;
	// evaluation is a function of material, board control, pawn control
	return (c1*value) + (c2*mobility) + (c3*pawns);
}

/**
 * method to let console know number of
 * game states evaluated as well as the score
 * the AI gave the board
 * @param s - the score
 * @param e - how many equivalent moves found
 */
void Computer::printData(int s, unsigned int e) {
	std::cout << "\n" << evalCount << " game states evaluated.\n";
	if (e > 1) {
		std::cout << "Found " << e << " equivalent moves; chose one stochastically.\n";
	}
	std::cout << (getColor() ? "White" : "Black");
	std::cout << " chose a move with score " << s << ".\n";
	evalCount = 0;
}

// accessor methods
unsigned int Computer::getDepth() { return depth; }

// mutator methods
void Computer::setDepth(unsigned int d) { depth = d; }