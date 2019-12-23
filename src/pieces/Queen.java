package pieces;

import static java.lang.Math.abs;

/**
 * Queen Piece class
 * @author Robert Scott, 4582342
 */
public class Queen extends Piece {
    /**
     * Queen constructor
     * @param c 
     */
    public Queen(Color c) {
        setType("Queen");
        setColor(c);
        setValue(800);
        setHasMoved(false);
    }
    @Override
    public boolean validMove(int x1, int y1, int x2, int y2) {
        // queen acts like bishop and rook, reuse that code
        boolean b1 = (abs(y1-y2) == abs(x1-x2)); // check if diff equal for r/c
        boolean b2 = (x1 == x2); // check if same col
        boolean b3 = (y1 == y2); // check if same row
        boolean b = (b1 || b2 || b3); // combine to make one truth statement
        return (b && onBoard(x2, y2)); // check if conditions met
    }
}
