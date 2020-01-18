#pragma once

// various game parameters

namespace GameParams {
	/**
	 * heuristic evaluation coefficients, each controls how much import is put
	 * upon a specific heuristic, a general guideline is  C1 > C3 > C2 with C1
	 * being fairly large in comparison and C2 generally being very small; for
	 * example: C1 = 12, C2 = 1, C3 = 3 or C1 = 20, C2 = 2, C3 = 5, and so on
	 */
	const static int C1 = 12; // for material value
	const static int C2 = 1; // for mobility value
	const static int C3 = 3; // for pawn rank value

	/**
	 * move buffer for AI, prevents move reduplication within the last few
	 * moves. This should be relatively small perhaps ideally in the single
	 * digits. Much larger and the AI will tend to forfeit early
	 */
	const static unsigned int BUFFER_SIZE = 3;

	/**
	 * piece values, generally keep this the way it is, there's no real need to
	 * change them
	 */
	const static unsigned int P_VAL = 1; // for pawns
	const static unsigned int N_VAL = 3; // for knights
	const static unsigned int B_VAL = 3; // for bishops
	const static unsigned int R_VAL = 5; // for rooks
	const static unsigned int Q_VAL = 9; // for queens
	const static unsigned int K_VAL = 100; // for kings

	/**
	 * game state values, generally keep this the way it is, there's no real
	 * need to change them
	 */
	const static int STALEMATE = 0;
	const static int DRAW = 0;
	const static int CHECK = 2; // check is multiplicand
	/**
	 * concerning checkmate scoring, it needs to be greater than any possible
	 * board evaluation. The highest material score for one player is 103,
	 * mobility score is 215 and pawn control 48. Multiply these by the
	 * coefficients and add one to ensure the evaluation is always highest for
	 * checkmate. It is multiplied by the value for check as check is equal to
	 * double any given board evaluation
	 */
	const static int CHECKMATE = (CHECK * ((C1*103) + (C2*215) + (C3*48))) + 1;

	/**
	 * default values
	 *
	const static int C1 = 12;
	const static int C2 = 1;
	const static int C3 = 3;
	const static unsigned int BUFFER_SIZE = 3;
	const static unsigned int P_VAL = 1;
	const static unsigned int N_VAL = 3;
	const static unsigned int B_VAL = 3;
	const static unsigned int R_VAL = 5;
	const static unsigned int Q_VAL = 9;
	const static unsigned int K_VAL = 100;
	const static int CHECKMATE = (CHECK * ((C1*103) + (C2*215) + (C3*48))) + 1;
	const static int STALEMATE = 0;
	const static int DRAW = 0;
	const static int CHECK = 2;
	 *
	 */
}
