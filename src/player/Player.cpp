#include "Player.hpp"

// Player class definition

/**
 * method to remove moves which would put player in check
 * @param m - movelist to remove moves from
 */
void Player::removeCheckedMoves(std::vector<Move> &m) {
	std::vector<int> indexes;
	for (unsigned int i = 0; i < m.size(); i++) {
		// make move on a copy and check if check
		Board* copy = new Board(*getBoard());
		copy->movePiece(m[i]);
		if (copy->determineCheck(getColor())) {
			indexes.insert(indexes.begin(), i);
		}
		delete copy;
	}
	for (unsigned int i = 0; i < indexes.size(); i++) {
		m.erase(m.begin() + indexes[i]);
	}
	indexes.clear();
}

// accessor methods
bool Player::getColor() { return color; }
Board* Player::getBoard() { return gameboard; }

// mutator methods
void Player::setColor(bool c) {	color = c; }
void Player::setBoard(Board* b) { gameboard = b; }