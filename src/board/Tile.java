package board;

import pieces.Piece;

/**
 * Tile class
 * @author Robert Scott, 4582342
 */
public class Tile {
    private Piece occupyingPiece; // piece which sits on tile
    /**
     * constructor for Tile
     */
    public Tile() {
        occupyingPiece = null; // originally blank (_)
    }
    /**
     * method which tells you if a piece is on tile
     * @return truth value
     */
    public boolean hasPiece() {
        return occupyingPiece != null;
    }
    /**
     * getter method to get piece
     * @return the piece on the tile
     */
    public Piece getPiece() {
        return occupyingPiece;
    }
    /**
     * method to set a new piece down
     * @param p the new piece
     */
    public void setPiece(Piece p){
        if(!hasPiece()) {
            occupyingPiece = p;
        }
    }
    /**
     * method to set a new piece replacing an old one
     * @return the old piece
     */
    public Piece capture() {
        Piece p;
        if (hasPiece()) {
            p = occupyingPiece;
            occupyingPiece = null;
            return p;
        } else {
            return null;
        }
    }
}
