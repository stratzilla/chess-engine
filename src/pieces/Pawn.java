package pieces;

/**
 * Pawn Piece class
 * @author Robert Scott, 4582342
 */
public class Pawn extends Piece {
    /**
     * Pawn constructor
     * @param c 
     */
    public Pawn(Color c) {
        setType("Pawn");
        setColor(c);
        setValue(100);
        setHasMoved(false);
    }
    @Override
    public boolean validMove(int x1, int y1, int x2, int y2) {
        int offset = 0;
        /**
         * since pawns move forward only, but what forward means
         * depends on color, use an offset. Negatives for black, positives
         * for white.
         */
        switch (getColor()) {
            case WHITE: offset = 1; break;
            case BLACK: offset = -1; break;
        }
        boolean b1 = ((x1 == x2) && (y1 - y2 == offset)); // move forward
        boolean b2 = ((x1 - x2 == -1) && (y1 - y2 == offset)); // capture to left
        boolean b3 = ((x1 - x2 == 1) && (y1 - y2 == offset)); // capture to right
        /**
         * if pawn has not moved, it can move forwards
         */
        boolean b4 = ((!getHasMoved() && x1 == x2) && (y1 - y2 == 2*offset));
        boolean b = (b1 ^ b2 ^ b3 ^ b4); // combine
        return (b && onBoard(x2, y2));
    }
}
