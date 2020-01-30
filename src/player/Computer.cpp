#include "Computer.hpp"

// Computer class definition, defines behavior of the AI controller player

/**
 * Computer class constructor
 * @param c - color of this player
 * @param d - the depth for AI tree search
 */
Computer::Computer(bool c, unsigned int d) {
	setColor(c);
	setDepth(d);
}

/**
 * method to prompt user for their move
 * @return - the move they've chosen
 */
Move Computer::promptMove() {
	return negamaxHandler(INT_MIN, INT_MAX);
}

/**
 * negamax handler, performs the first level of negamax and compares the values
 * of further calls to generate the best move as dictated by the AI
 * @param alf - alpha
 * @param bet - beta
 * @return - optimal AI move
 */
Move Computer::negamaxHandler(int alf, int bet) {
	// get all moves AI can make
	std::vector<Move> moveList = getBoard()->getAllMoves(!getColor());
	// remove moves which would put AI in check
	removeCheckedMoves(moveList);
	int bestMoveValue = INT_MIN; // initially -inf
	std::vector<Move> bestMoves; // collection of best moves
	// for each possible move
	for (unsigned int i = 0; i < moveList.size(); i++) {
		/**
		 * to avoid threefold repetition, we need to handle cases where a move
		 * is repeated. Mostly evident in AI vs AI games where it will go on
		 * forever as they move pieces back and forth ad infinitum. This
		 * prevents reuse of the previous moves the amount of which is
		 * determined by a buffer. Added benefits of less negamax calls meaning
		 * faster speed
		 */
		std::string toFind = moveList[i].stateMove();
		if (std::find(buffer.begin(), buffer.end(), toFind) != buffer.end()) {
			continue; // if move found in buffer, don't perform negamax
		}
		Board* copy = new Board(*getBoard()); // make a new board copy
		copy->movePiece(moveList[i]); // make move on copy
		// find value of that move
		int v = -negamax(copy, getDepth()-1, -bet, -alf, !getColor());
		delete copy;
		// if same worth or not enough to fill queue
		if (v == bestMoveValue || moveList.size() <= GameParams::BUFFER_SIZE) {
			// add it to the collection
			bestMoves.push_back(moveList[i]);
		} else if (v > bestMoveValue) {
			// add it to the list of possible moves and update best score
			bestMoveValue = v;
			bestMoves.clear(); // don't need worse moves
			bestMoves.push_back(moveList[i]);
		}
		// update alpha if better best move value
		if (bestMoveValue > alf) { alf = bestMoveValue;	}
		// prune further moves
		if (alf >= bet) { pruneCount++; break; }
	}
	/**
	 * unable to catch instances where the movelist is zero leading to null
	 * move, so consider this the AI forfeiting
	 */
	if (bestMoves.size() == 0) {
		std::cout << (getColor() ? "White" : "Black");
		std::cout << " has forfeited the game.\n\n";
		exit(0); // impossible to unwrap into main()
	}
	/**
	 * because some moves will be worth the same as others, AI will have a
	 * collection of the best moves here. Choose one stochastically
	 */
	Move theBestMove = bestMoves[rand() % bestMoves.size()];
	buffer.push_back(theBestMove.stateMove()); // add best move to buffer
	// keep buffer size consistent
	if (buffer.size() > GameParams::BUFFER_SIZE) {
		buffer.erase(buffer.begin());
	}
	// find the value of that move
	Board* copy = new Board(*getBoard());
	copy->movePiece(theBestMove);
	// if move checkmates opponent
	if (copy->determineCheckmate(!getColor())) {
		bestMoveValue = GameParams::CHECKMATE;
	// if move stalemates
	} else if (copy->determineStalemate(!getColor())) {
		bestMoveValue = GameParams::STALEMATE;
	// if move draws
	} else if (copy->determineDraw()) {
		bestMoveValue = GameParams::DRAW;
	// if move puts opponent in check
	} else if (copy->determineCheck(!getColor())) {
		bestMoveValue = GameParams::CHECK * evalBoard(copy);
	// otherwise vanilla value
	} else {
		bestMoveValue = evalBoard(copy);
	}
	delete copy;
	printData(bestMoveValue, bestMoves.size()); // show some data
	return theBestMove;
}

/**
 * negamax implementation using alpha-beta pruning, will search tree space
 * recursively but without the typical two function calls that minimax uses
 * negamax relies on the property of max(alf, bet) == -min(-alf, -bet) which is
 * equivalent or better than vanilla minimax
 * @param b - the board to checkmate
 * @param d - the depth to use to break out of algorithm
 * @param alf - alpha
 * @param bet - beta
 * @param p - the calling player
 * @return - best evaluation for AI
 */
int Computer::negamax(Board* b, unsigned int d, int alf, int bet, bool p) {
	evalCount++; // increment count to display positions evaluated
	int offset = (p == getColor() ? 1 : -1); // vary based on color
	// terminal cases would be stalemate or checkmate or depth zero
	if (d == 0) { return offset * evalBoard(b); }
	// consider a checkmate as worst possible position
	if (b->determineCheckmate(p)) { return -GameParams::CHECKMATE; }
	// consider a stalemate as neither good or bad
	if (b->determineStalemate(p)) { return GameParams::STALEMATE; }
	// likewise for draw
	if (b->determineDraw()) { return GameParams::DRAW; }
	// putting another person in check is beneficial
	if (b->determineCheck(p)) {
		return (GameParams::CHECK * offset) * evalBoard(b);
	}
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
		if (alf >= bet) { pruneCount++; break; } // cutoff for branches
	}
	return value;
}

/**
 * method to evaluate a board's worth
 * @param b - the board to evaluate
 * @return - total board value according to AI
 */
int Computer::evalBoard(Board* b) {
	/**
	 * board evaluation is done in three steps:
	 *  1. find the material of all pieces
	 *  2. find the mobility of all pieces
	 *  3. find the pawn control
	 * then evaluation considers the total board value plus the board control
	 * plus pawn control
	 */
	int value = b->getAllPieceValues(getColor()); // material value
	int mobility = b->getAllMobilityValues(getColor()); // board control
	int pawns = b->getAllPawnValues(getColor()); // pawn control
	/**
	 * some coefficients to balance the weights of the various metrics about
	 * the board
	 */
	int c1 = GameParams::C1, c2 = GameParams::C2, c3 = GameParams::C3;
	// will elide if any coefficient is zero
	return (c1*value) + (c2*mobility) + (c3*pawns);
}

/**
 * method to let console know number of game states evaluated as well as the
 * score the AI gave the board
 * @param s - the score
 * @param e - how many equivalent moves found
 */
inline void Computer::printData(int s, unsigned int e) {
	std::cout << "\n" << evalCount << " game state(s) evaluated; ";
	std::cout << pruneCount << " pruned.\n";
	if (e > 1) {
		std::cout << "Found " << e << " equivalent moves; ";
		std::cout << "chose one stochastically.\n";
	}
	std::cout << (getColor() ? "White" : "Black");
	std::cout << " chose a move with score " << s << ".\n";
	evalCount = 0; pruneCount = 0;
}

// accessor methods
unsigned int Computer::getDepth() { return depth; }

// mutator methods
void Computer::setDepth(unsigned int d) { depth = d; }
