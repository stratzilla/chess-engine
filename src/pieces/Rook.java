package pieces;

/**
 * Rook Piece class
 * @author Robert Scott, 4582342
 */
public class Rook extends Piece {
    /**
     * Rook constructor
     * @param c 
     */
    public Rook(Color c) {
        setType("Rook");
        setColor(c);
        setValue(400);
        setHasMoved(false);
    }
    @Override
    public boolean validMove(int x1, int y1, int x2, int y2) {
        boolean b1 = (x1 == x2); // can move only in straight lines
        boolean b2 = (y1 == y2); // up/down or left/right, so ident. col or row
        boolean b = (b1 || b2); // combine to make one truth statement
        return (b && onBoard(x2, y2)); // check if conditions met
    }
}
