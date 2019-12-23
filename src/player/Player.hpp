#pragma once
#include "../game/Move.hpp"
#include "../board/Board.hpp"

/**
 * Player class declaration
 * base class for derived players
 */
class Player {
	private:
		// to avoid magic numbers
		const static bool WHITE = true, BLACK = false;
	
		Board* gameboard; // the board the player is playing
		bool color; // color of the player
	protected:
		// protected member methods
		void removeCheckedMoves(std::vector<Move>&);
		
		// protected accessor methods
		Board* getBoard();
	public:
		// member methods
		virtual Move promptMove(bool);
		
		// public accessor methods
		bool getColor();
		
		// mutator methods
		void setColor(bool);
		void setBoard(Board*);
};