
package pieces;

import static java.lang.Math.abs;

/**
 * King Piece class
 * @author Robert Scott, 4582342
 */
public class King extends Piece {
    /**
     * King constructor
     * @param c 
     */
    public King(Color c) {
        setType("King");
        setColor(c);
        setValue(50000);
        setHasMoved(false);
    }
    @Override
    public boolean validMove(int x1, int y1, int x2, int y2) {
        boolean c1 = !getHasMoved(); // can't castle if moved
        boolean c2 = ((y1 == y2) && abs(x1 - x2) == 2); // check if correct pos
        boolean c = (c1 && c2); // combine to make one truth statement
        boolean b1 = (abs(x1 - x2) == 1 && abs(y1 - y2) == 1); // if move diag
        boolean b2 = (abs(x1 - x2) == 0 && abs(y1 - y2) == 1); // if move row
        boolean b3 = (abs(x1 - x2) == 1 && abs(y1 - y2) == 0); // if move col
        boolean b = (b1 || b2 || b3); // combine to make one truth statement
        return ((c || b) && onBoard(x2, y2)); // check if conditions met
    }
}
