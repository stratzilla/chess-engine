package pieces;

/**
 * Piece class
 * @author Robert Scott, 4582342
 */
public class Piece {
    private String type; // type of piece it is
    private Color color; // color of piece
    private int value; // value of piece
    private boolean hasMoved; // if piece has moved
    /**
     * method to determine if piece is on board
     * @param x x position
     * @param y y position
     * @return truth value
     */
    protected boolean onBoard(int x, int y) {
        boolean ns = (x >= 0 && x <= 7); // north south
        boolean we = (y >= 0 && y <= 7); // west east
        return (ns && we);
    }
    /**
     * setter method to change piece type
     * @param s new type
     */
    public void setType(String s) {
        type = s;
    }
    /**
     * setter method to change piece color
     * @param c new color
     */
    public void setColor(Color c) {
        color = c;
    }
    /**
     * setter method to change piece value
     * @param i new value
     */
    public void setValue(int i) {
        int offset = 0;
        switch(getColor()) { // different for W/B
            case WHITE: offset = 1; break;
            case BLACK: offset = -1; break;
        }
        value = (i*offset);
    }
    /**
     * setter method to change if piece has moved
     * @param b new truth value
     */
    public void setHasMoved(boolean b) {
        hasMoved = b;
    }
    /**
     * the below are just the getter methods for the attributes
     * @return 
     */
    public String getType() {
        return type;
    }
    public Color getColor() {
        return color;
    }
    public int getValue() {
        return value;
    }
    public boolean getHasMoved() {
        return hasMoved;
    }
    /**
     * method to parse symbol from type
     * @return 
     */
    public char getSymbol() {
        char symbol = ' ';
        switch (getColor()) {
            case WHITE:
                switch(type) {
                    case "Knight": symbol = 'N'; break;
                    case "Bishop": symbol = 'B'; break;
                    case "Rook": symbol = 'R'; break;
                    case "Queen": symbol = 'Q'; break;
                    case "King": symbol = 'K'; break;
                    case "Pawn": symbol = 'P'; break;
                }
                break;
            case BLACK:
                switch(type) {
                    case "Knight": symbol = 'n'; break;
                    case "Bishop": symbol = 'b'; break;
                    case "Rook": symbol = 'r'; break;
                    case "Queen": symbol = 'q'; break;
                    case "King": symbol = 'k'; break;
                    case "Pawn": symbol = 'p'; break;
                }
                break;
        }
        return symbol;
    }
    /**
     * not implemented here but in member functions
     * could this be abstract?
     */
    public boolean validMove(int x1, int y1, int x2, int y2) {
        return false;
    }
}
