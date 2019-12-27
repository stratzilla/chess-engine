#pragma once

/**
 * various game parameters
 */

namespace GameParams {
	// heuristic evaluation coefficients
	const static int C1 = 12; // for material value
	const static int C2 = 1; // for mobility value
	const static int C3 = 3; // for pawn rank value
	
	// move buffer
	const static unsigned int BUFFER_SIZE = 3;
	
	// piece values
	const static unsigned int P_VAL = 1; // for pawns
	const static unsigned int N_VAL = 3; // for knights
	const static unsigned int B_VAL = 3; // for bishops
	const static unsigned int R_VAL = 5; // for rooks
	const static unsigned int Q_VAL = 9; // for queens
	const static unsigned int K_VAL = 100; // for kings
	
	// game condition board evals
	const static int CHECKMATE = 50000000;
	const static int STALEMATE = 0;
	const static int DRAW = 0;
	
	/**
	 * default values
		// heuristic evaluation coefficients
		const static int C1 = 12; // for material value
		const static int C2 = 1; // for mobility value
		const static int C3 = 3; // for pawn rank value
		
		// move buffer
		const static unsigned int BUFFER_SIZE = 3;
		
		// piece values
		const static int P_VAL = 1; // for pawns
		const static int N_VAL = 3; // for knights
		const static int B_VAL = 3; // for bishops
		const static int R_VAL = 5; // for rooks
		const static int Q_VAL = 9; // for queens
		const static int K_VAL = 100; // for kings
		
		// game condition board evals
		const static int CHECKMATE = 5000000;
		const static int STALEMATE = 0;
		const static int DRAW = 0;
	 *
	 */
}