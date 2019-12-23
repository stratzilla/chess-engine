package board;

import static java.lang.Math.abs;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import pieces.*;
import static pieces.Color.BLACK;
import static pieces.Color.WHITE;

/**
 * Board class
 * @author Robert Scott, 4582342
 */
public class Board {
    private Tile[][] gameBoard; // the game board
    /**
     * constructor for board class
     */
    public Board() {
        /**
         * board is an 8x8 grid of Tiles
         */
        gameBoard = new Tile[8][8];
    }
    /**
     * getter method to grab the game board
     * @return 
     */
    public Tile[][] getBoard() {
        return gameBoard;
    }
    /**
     * method to move piece
     * @param m the proposed move to make
     * @return the moved piece
     */
    public Piece move(Move m) {
        boolean b1, b2, b3; // used for readability, holy cow some of these can get long
        int[] curr = m.getCurr(); // get the current position from move
        int[] dest = m.getDest(); // likewise for destination
        Tile currTile = gameBoard[curr[0]][curr[1]]; // get the current tile from pos
        Tile destTile = gameBoard[dest[0]][dest[1]]; // likewise for destination
        Piece currPiece = currTile.getPiece(); // and get piece on said tile
        Piece destPiece = null; // and so on
        if(!currTile.hasPiece()) { // if no piece to move
            return null; // return no piece
        } else {
            if (destTile.hasPiece()) { // if piece occupying destination
                destPiece = destTile.capture(); // capture it
            } // TODO: add color check
            destTile.setPiece(currTile.capture()); // place piece there
            /**
             * specific for castling, preconfigured areas to castle in
             */
            if(gameBoard[dest[0]][dest[1]].getPiece().getType().equals("King")) {
                if(abs(dest[0]-curr[0]) == 2) { // if king in right spot
                    if(dest[0] == 6) { // if you pocket king on 6th col
                        int[] newDest = {5, dest[1]}; // place to 5th
                        movePiece(curr, newDest);
                    } else if (dest[0] == 2) { // or 2nd col, other side
                        int[] newDest = {3, dest[1]}; // place to 3rd
                        movePiece(curr, newDest);
                    }
                }
            }
            return destPiece; // pop the piece for minimax
        }
    }
    /**
     * method which moves a piece from one tile to another
     * @param from current position
     * @param to destination position
     */
    public void movePiece(int[] from, int[] to) {
        Tile toTile = gameBoard[to[0]][to[1]];
        Tile fromTile = gameBoard[from[0]][from[1]];
        toTile.setPiece(fromTile.getPiece());
    }
    /**
     * method to check if a move is valid or not
     * @param from current position
     * @param to dest position
     * @return truth value
     */
    public boolean isValidMove(int[] from, int[] to) {
        boolean b1 = gameBoard[from[0]][from[1]].hasPiece();
        boolean b2 = gameBoard[from[0]][from[1]].getPiece().validMove(from[0], from[1], to[0], to[1]);
        return (b1 && b2);
    }
    /**
     * method to check if a position contains your own piece
     * @param x x pos
     * @param y y pos
     * @param c your color
     * @return truth value
     */
    public boolean ownPiece(int x, int y, Color c) {
        boolean b1 = gameBoard[x][y].hasPiece();
        boolean b2 = gameBoard[x][y].getPiece().getColor() == c;
        if (b1 && b2) {
            return true;
        }
        return false;
    }
    
    /**
     * method to determine if there's a clear path from a to b
     * @param from curr pos
     * @param to dest pos
     * @param p moving piece
     * @return truth value
     */
    public boolean isRoom(int[] from, int[] to, Piece p) {
        boolean b1, b2, b3, b4, b5, b6, b7;
        switch (p.getType()) { // find type of piece
            /**
             * rooks cannot move over other pieces
             */
            case "Rook":
                b1 = (from[1] == to[1]); // rooks can move hor. or vert. only
                b2 = (from[0] == to[0]);
                if (!b1 && b2) { // if moving hor.
                    b3 = (from[1] < to[1]); // if moving one direction
                    if (b3) {
                        /**
                         * check tiles in its way to see if pieces exist
                         */
                        for (int i = from[1]+1; i < to[1]; i++) {
                            b4 = gameBoard[from[0]][i].hasPiece();
                            if (b4) { return false; } // if occluding piece
                        }
                    } else { // or other direction
                        for (int i = from[1]-1; i > to[1]; i--) {
                            b4 = gameBoard[from[0]][i].hasPiece();
                            if (b4) { return false; }
                        }
                    }
                } else if (b1 && !b2) { // if moving vert.
                    b3 = (from[0] < to[0]);
                    if (b3) {
                        for (int i = from[0]+1; i < to[0]; i++) {
                            b4 = gameBoard[i][from[0]].hasPiece();
                            if (b4) { return false; }
                        }
                    } else {
                        for (int i = from[0]-1; i > to[0]; i--) {
                            b4 = gameBoard[i][from[0]].hasPiece();
                            if (b4) { return false; }
                        }
                    }
                }
                return true; // if no pieces found, clear path
            /**
             * knights CAN move over pieces, however, in all cases
             */
            case "Knight":
                return true; // always clear path
            /**
             * like rooks, bishops cannot move over pieces
             */
            case "Bishop":
                b1 = (from[0] < to[0]); // if diagonal one direction
                b2 = (from[1] < to[1]); // same
                if (b1 && b2) { // if diag. one direction
                    /**
                     * check for occluding pieces like with rook
                     */
                    for (int i = from[0]+1, j = from[1]+1; i < to[0] && j < to[1]; i++, j++) {
                        b3 = gameBoard[i][j].hasPiece();
                        if (b3) { return false; }
                    }
                } else if (b1 && !b2) { // or another diag. direction
                    for (int i = from[0]+1, j = from[1]-1; i < to[0] && j > to[1]; i++, j--) {
                        b3 = gameBoard[i][j].hasPiece();
                        if (b3) { return false; }
                    }
                } else if (!b1 && b2) { // or another
                    for (int i = from[0]-1, j = from[1]+1; i > to[0] && j < to[1]; i--, j++) {
                        b3 = gameBoard[i][j].hasPiece();
                        if (b3) { return false; }
                    }
                } else if (!b1 && !b2) { // or another
                    for (int i = from[0]-1, j = from[1]-1; i > to[0] && j > to[1]; i--, j--) {
                        b3 = gameBoard[i][j].hasPiece();
                        if (b3) { return false; }
                    }
                }
                return true; // if no occluding pieces, clear path, let it move
            /**
             * pawns cannot move over pieces
             */
            case "Pawn":
                int offset = (from[1] - to[1]); // since paws move depending on color
                if (from[0] == to[0]) {
                    switch(offset) {
                        case 2: // if moving forward two places (white)
                            b1 = gameBoard[from[0]][from[1]-1].hasPiece();
                            b2 = gameBoard[to[0]][to[1]].hasPiece();
                            return (!b1 && !b2);
                        case -2: // black
                            b1 = gameBoard[from[0]][from[1]+1].hasPiece();
                            b2 = gameBoard[to[0]][to[1]].hasPiece();
                            return (!b1 && !b2);
                        case 1: // if moving forward one places (white)
                            b1 = gameBoard[to[0]][to[1]].hasPiece();
                            return !b1;
                        case -1: // black
                            b1 = gameBoard[to[0]][to[1]].hasPiece();
                            return !b1;
                    }
                /**
                 * or if capturing a piece, it can move diagonal 1 (ie. up1, side1)
                 */
                } else if (abs(from[0] - to[0]) == 1 && abs(from[1] - to[1]) == 1) {
                    b1 = gameBoard[to[0]][to[1]].hasPiece();
                    return b1;
                }
                return false; // otherwise occluded
            /**
             * queens are just rooks and bishops together. reuse code from earlier
             */
            case "Queen": 
                b1 = (from[0] < to[0]);
                b2 = (from[1] < to[1]);
                if (b1 && b2) {
                    for (int i = from[0]+1, j = from[1]+1; i < to[0] && j < to[1]; i++, j++) {
                        b3 = gameBoard[i][j].hasPiece();
                        if (b3) { return false; }
                    }
                } else if (b1 && !b2) {
                    for (int i = from[0]+1, j = from[1]-1; i < to[0] && j > to[1]; i++, j--) {
                        b3 = gameBoard[i][j].hasPiece();
                        if (b3) { return false; }
                    }
                } else if (!b1 && b2) {
                    for (int i = from[0]-1, j = from[1]+1; i > to[0] && j < to[1]; i--, j++) {
                        b3 = gameBoard[i][j].hasPiece();
                        if (b3) { return false; }
                    }
                } else if (!b1 && !b2) {
                    for (int i = from[0]-1, j = from[1]-1; i > to[0] && j > to[1]; i--, j--) {
                        b3 = gameBoard[i][j].hasPiece();
                        if (b3) { return false; }
                    }
                }
                b1 = (from[1] == to[1]);
                b2 = (from[0] == to[0]);
                if (!b1 && b2) {
                    b3 = (from[1] < to[1]);
                    if (b3) {
                        for (int i = from[1]+1; i < to[1]; i++) {
                            b4 = gameBoard[from[0]][i].hasPiece();
                            if (b4) { return false; }
                        }
                    } else {
                        for (int i = from[1]-1; i > to[1]; i--) {
                            b4 = gameBoard[from[0]][i].hasPiece();
                            if (b4) { return false; }
                        }
                    }
                } else if (b1 && !b2) {
                    b3 = (from[0] < to[0]);
                    if (b3) {
                        for (int i = from[0]+1; i < to[0]; i++) {
                            b4 = gameBoard[i][from[0]].hasPiece();
                            if (b4) { return false; }
                        }
                    } else {
                        for (int i = from[0]-1; i > to[0]; i--) {
                            b4 = gameBoard[i][from[0]].hasPiece();
                            if (b4) { return false; }
                        }
                    }
                }
                return true;
            /**
             * Kings cannot move over pieces
             */
            case "King":
                // if castling, can only do if unmoved
                b1 = gameBoard[from[0]][from[1]].getPiece().getHasMoved();
                if (!b1) { // if hasn't moved
                    /**
                     * castling specific things, refer to prior method
                     */
                    if (from[0] == 4 && from[0] - to[0] == 2) {
                        /**
                         * check for occlusion to right
                         */
                        b2 = gameBoard[from[0] - 3][from[1]].hasPiece();
                        b3 = gameBoard[from[0] - 2][from[1]].hasPiece();
                        b4 = gameBoard[from[0] - 1][from[1]].hasPiece();
                        Piece temp = gameBoard[from[0] - 4][from[1]].getPiece();
                        b5 = (temp == null);
                        b6 = temp.getHasMoved();
                        b7 = temp.getType().equals("Rook");
                        return (!b2 && !b3 && !b4 && !b5 && b6 && b7);
                    } else if (from[0] == 4 && from[0] - to[0] == -2) {
                        /**
                         * and to left
                         */
                        b2 = gameBoard[from[0] + 2][from[1]].hasPiece();
                        b3 = gameBoard[from[0] + 1][from[1]].hasPiece();
                        Piece temp = gameBoard[from[0] + 3][from[1]].getPiece();
                        b4 = (temp == null);
                        b5 = temp.getHasMoved();
                        b6 = temp.getType().equals("Rook");
                        return (!b2 && !b3 && !b4 && b5 && b6);
                    }
                }
                // otherwise regular move
                b2 = (abs(from[0] - to[0]) == 1 && abs(from[1] - to[1]) == 0); // horizontal
                b3 = (abs(from[0] - to[0]) == 1 && abs(from[1] - to[1]) == 1); // diagonal
                b4 = (abs(from[0] - to[0]) == 0 && abs(from[1] - to[1]) == 1); // vertical
                return (b2 || b3 || b4);
        }
        return false;
    }
    
    /**
     * method to get all the moves of a given piece, used by AI
     * @param c - the color of the player
     * @param xy - position of piece
     * @return list of moves
     */
    public ArrayList<int[]> getMoves(Color c, int[] xy) {
        boolean b1, b2, b3, b4, b5, b6, b7;
        ArrayList<int[]> moves = new ArrayList<int[]>(); // init list
        Piece p = gameBoard[xy[0]][xy[1]].getPiece(); // piece to check moves on
        b1 = (p == null); // if piece doesn't exist
        if (!b1) {
            b2 = (c == p.getColor()); // if matching color
            if (b2) {
                /**
                 * check all board positions
                 */
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        int[] newPos = new int[2]; // position of temporary tile
                        newPos[0] = i;
                        newPos[1] = j;
                        b3 = isValidMove(xy, newPos); // check if moving there is possible
                        b4 = isRoom(xy, newPos, p); // check if theres room
                        b5 = gameBoard[i][j].hasPiece(); // check if it has a piece
                        b6 = (gameBoard[i][j].getPiece().getColor() == c); // check if the color patches
                        b7 = intoCheck(xy, newPos); // check if it would bring you into check
                        if (b3 && b4 && (!b5 || !b6) && !b7) {
                            moves.add(newPos); // add valid move to list
                        }
                    }
                }
            }            
        }
        return moves;
    }
    
    /**
     * method to determine if you're in check
     * @param from curr pos
     * @param to dest pos
     * @return truth value
     */
    public boolean intoCheck(int[] from, int[] to) {
        //TODO
        return false;
    }
    /**
     * method to check if king is threatened
     * @param c the color of the king
     * @return truth value
     */
    public boolean kingThreatened(Color c) {
        boolean b1, b2;
        /**
         * check all positions
         */
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                b1 = gameBoard[i][j].hasPiece(); // if position has a piece
                b2 = gameBoard[i][j].getPiece().getColor() != c; // if opposing color
                if (b1 && b2) {
                    int[] xy = new int[2]; // create new pos
                    xy[0] = i;
                    xy[1] = j;
                    if (pieceThreatensKing(xy)) { // check if the piece threatens king
                        return true;
                    }
                }
            }
        }
        return false;
    }

    /**
     * method to check if a piece threatens the king
     * @param xy position of piece to check
     * @return 
     */
    public boolean pieceThreatensKing(int[] xy) {
        boolean b1, b2, b3;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                b1 = gameBoard[i][j].hasPiece(); // if piece exists
                b2 = gameBoard[i][j].getPiece().getType().equals("King"); // if piece is king
                b3 = gameBoard[i][j].getPiece().getColor().equals(gameBoard[xy[0]][xy[1]].getPiece().getColor());
                if (b1 && b2 && b3) {
                    return true;
                }
            }
        }
        return false;
    }
    
    /**
     * method to set up the game board
     */
    public void initializeBoard() {
        BufferedReader br;
        String filename = "board.txt"; // read from file
        try {
            br = new BufferedReader(new InputStreamReader(new FileInputStream(filename)));
            int c;
            int count = 0;
            while ((c = br.read()) != -1) {
                char aChar = (char) c;
                if (aChar != '\n' && aChar != '\r') {
                    placePiece(aChar, count);
                    count++;
                }
            }            
        } catch (Exception ex) {
            System.out.println("Board not defined: " + ex);
        }
    }
    
    /**
     * method to populate the board
     * @param c piece symbol
     * @param i index
     */
    private void placePiece(char c, int i) {
        Tile t = new Tile();
        Piece p;
        int y = i % 8;
        int x = (int)(i / 8);
        //System.out.println("x: "+x+", y: "+y+" === "+c);
        switch (c) {
            case 'r': p = new Rook(BLACK); break;
            case 'n': p = new Knight(BLACK); break;
            case 'b': p = new Bishop(BLACK); break;
            case 'p': p = new Pawn(BLACK); break;
            case 'q': p = new Queen(BLACK); break;
            case 'k': p = new King(BLACK); break;
            case 'R': p = new Rook(WHITE); break;
            case 'N': p = new Knight(WHITE); break;
            case 'B': p = new Bishop(WHITE); break;
            case 'P': p = new Pawn(WHITE); break;
            case 'Q': p = new Queen(WHITE); break;
            case 'K': p = new King(WHITE); break;
            default: p = null; break;
        }
        t.setPiece(p);
        gameBoard[x][y] = t;
    }
    
    /**
     * method to copy board for undoing moves
     * @return a copy of this.board
     */
    public Board copyBoard() {
        Board newBoard = new Board();
        Piece q = null;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Tile t = new Tile();
                if (gameBoard[i][j].hasPiece()) {
                    Piece p = gameBoard[i][j].getPiece();
                    switch(p.getSymbol()) {
                        case 'r': q = new Rook(BLACK); break;
                        case 'n': q = new Knight(BLACK); break;
                        case 'b': q = new Bishop(BLACK); break;
                        case 'p': q = new Pawn(BLACK); break;
                        case 'q': q = new Queen(BLACK); break;
                        case 'k': q = new King(BLACK); break;
                        case 'R': q = new Rook(WHITE); break;
                        case 'N': q = new Knight(WHITE); break;
                        case 'B': q = new Bishop(WHITE); break;
                        case 'P': q = new Pawn(WHITE); break;
                        case 'Q': q = new Queen(WHITE); break;
                        case 'K': q = new King(WHITE); break;
                    }
                t.setPiece(q);
                newBoard.getBoard()[i][j] = t;
                }
            }
        }
        return newBoard;
    }
    
    /**
     * method to display the game board
     */
    public void displayBoard() {
        System.out.print("  ");
        for (int i = 0; i < 8; i++) {
            System.out.print((char)('a' + i) + " ");
        }
        System.out.println();
        for (int i = 0; i < 8; i++) {
            System.out.print(8 - i + " ");
            for (int j = 0; j < 8; j++) {
               if(gameBoard[i][j].getPiece() == null) {
                    System.out.print("_ ");
                } else {
                    System.out.print(gameBoard[i][j].getPiece().getSymbol() + " ");
                }
            }
            System.out.println();
        }
    }
    
}
