package pieces;

import static java.lang.Math.abs;

/**
 * Knight Piece class
 * @author Robert Scott, 4582342
 */
public class Knight extends Piece {
    /**
     * Knight constructor
     * @param c 
     */
    public Knight(Color c) {
        setType("Knight");
        setColor(c);
        setValue(300);
        setHasMoved(false);
    }
    @Override
    public boolean validMove(int x1, int y1, int x2, int y2) {
        // L shape is consistently a difference of 2 and 1 in one and other dir
        boolean b1 = (abs(x1 - x2) == 2 && abs(y1 - y2) == 1);
        boolean b2 = (abs(x1 - x2) == 1 && abs(y1 - y2) == 2);
        boolean b = (b1 || b2); // combine to make one truth statement
        return (b && onBoard(x2, y2)); // check if conditions met
    }
}
