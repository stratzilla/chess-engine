
package pieces;

import static java.lang.Math.abs;

/**
 * Bishop Piece class
 * @author Robert Scott, 4582342
 */
public class Bishop extends Piece {
    /**
     * constructor for Bishop
     * @param c 
     */
    public Bishop(Color c) {
        /**
         * populate fields of Piece
         */
        setType("Bishop");
        setColor(c);
        setValue(325);
        setHasMoved(false);
    }
    /**
     * method to describe the movement of a Bishop
     * @param x1 current x
     * @param y1 current y
     * @param x2 destination x
     * @param y2 destination y
     * @return if a move is possible
     */
    @Override
    public boolean validMove(int x1, int y1, int x2, int y2) {
        /**
         * Bishops can only move diagonally, and an easy way to confirm
         * a diagonal movement is made is to compare the distance in x to
         * the distance of y. Equivalence means diagonal move
         */
        boolean b = (abs(y1-y2) == abs(x1-x2)); // check if diff equal for r/c
        return (b && onBoard(x2, y2)); // find if conditions met
    }
}
