package game;

import board.Board;
import board.Move;
import java.util.ArrayList;
import pieces.Color;
import static pieces.Color.BLACK;
import static pieces.Color.WHITE;
import pieces.Piece;

/**
 * AI class
 * @author Robert Scott, 4582342
 */
public class AI extends Player {
    
    public Move bestMove;
    private int depth = 5;
        
    /**
     * method to find the best move possible using minimax
     * @param b the board to check
     * @param check whether AI is in check or not
     * @return the best move
     */
    public Move getBestMove(Board b) {
        Board tempB = b.copyBoard(); // copy board so it's not altered
        Max(b, Integer.MIN_VALUE, Integer.MAX_VALUE, depth);
        return bestMove;
    }
    
    /**
     * Max portion of minimax function
     * @param b - game board
     * @param alf - alpha
     * @param bet - beta
     * @param d - depth to search for
     * @return value of a move
     */
    private int Max(Board b, int alf, int bet, int d) {
        Piece p; // potential piece to move
        ArrayList<Move> moves = getMoves(b, BLACK); // find all possible moves on board
        if (d <= 0) { // base case
            return tally(b); // return value
        }
        if (!moves.isEmpty()) { // if moves exist
            Move m = moves.remove(0); // take 1st move as example
            Board tempBoard = b.copyBoard(); // make a temp board to undo later
            p = b.move(m); // perform the move
            int value = Min(b, alf, bet, d-1); // find minimized value for next depth level
            if (value >= bet) { // if value is greater than beta, don't need to consider those nodes
                b = null; // remove board
                b = tempBoard.copyBoard(); // replace with original board to backtrack
                return bet;
            }
            if (value > alf) { // otherwise, you're approaching best move
                if (d == depth) { // check if reached desired depth
                    bestMove = m; // if so, take the best move found with pruning
                }
                alf = value; // or assume alpha is ideal score
            }
            b = tempBoard; // undo move
        }
        return alf;
    }
    
    /**
     * Min portion of minimax function
     * @param b the board
     * @param alf alpha
     * @param bet beta
     * @param d depth
     * @return value
     */
    public int Min(Board b, int alf, int bet, int d) {
        ArrayList<Move> moves = getMoves(b, WHITE);
        Piece p;
        if (d <= 0) {
            return tally(b);
        }
        if (moves != null) {
            Move m = moves.remove(0);
            Board tempBoard = b.copyBoard();
            p = b.move(m);
            int value = Max(b, alf, bet, d-1);
            if (value <= alf) {
                b = null;
                b = tempBoard.copyBoard();
                return alf;
            }
            if (value < bet) {
                if (d == depth) {
                    bestMove = m;
                }
                bet = value;
            }
            b = tempBoard;
        }
        return bet;
    }
    
    /**
     * method to evaluate board score
     * @param b the board to score
     * @return the score
     */
    private int tally(Board b) {
        int totalValue = 0;
        int offset; // needed for B/W difference
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (b.getBoard()[i][j].hasPiece()) { // if piece exists
                    if (b.getBoard()[i][j].getPiece().getColor() == WHITE) {
                        offset = 1; // +score
                    } else {
                        offset = -1; // -score
                    }
                    int inc = b.getBoard()[i][j].getPiece().getValue()*offset;
                }
            }
        }
        return totalValue;
    }
    /**
     * method to get all the possible moves on a board
     * @param b the board to check
     * @param c the color to check
     * @return the list of moves
     */
    private ArrayList<Move> getMoves(Board b, Color c) {
        boolean b1, b2;
        int[] xy = new int[2];
        ArrayList<Move> moves = new ArrayList<Move>();
        ArrayList<Move> subMoves = new ArrayList<Move>();
        ArrayList<int[]> boardMoves = new ArrayList<int[]>();
        /**
         * check all board positions
         */
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                b1 = b.getBoard()[i][j].hasPiece(); // moves found from existing pieces
                b2 = (b.getBoard()[i][j].getPiece().getColor() == c); // if matching color
                if (b1 && b2) {
                    xy[0] = i;
                    xy[1] = j;
                    /**
                     * populate the list with moves
                     */
                    boardMoves = b.getMoves(c, xy);
                    for(int[] k : boardMoves) {
                        moves.add(new Move(i, j, k[0], k[1]));
                    }
                }
            }
        }
        return moves;
    }
   
}
