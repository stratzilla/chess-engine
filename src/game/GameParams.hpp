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
	const static int P_VAL = 1; // for pawns
	const static int N_VAL = 3; // for knights
	const static int B_VAL = 3; // for bishops
	const static int R_VAL = 5; // for rooks
	const static int Q_VAL = 9; // for queens
	const static int K_VAL = 100; // for kings
	
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
	 *
	 */
}