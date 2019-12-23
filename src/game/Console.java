package game;

import board.Board;
import board.Move;
import java.util.Scanner;
import static pieces.Color.BLACK;
import static pieces.Color.WHITE;
import pieces.Piece;

/**
 * Console class
 * controls the game and provides a frontend to the user
 * @author Robert Scott, 4582342
 */
public class Console {
    private Board gameBoard; // the current game board
    private boolean gameOver; // to determine when game is over
    
    /**
     * Console constructor
     */
    public Console() {
        gameOver = false; // initially game is not over
        gameBoard = new Board(); // instantiate game board
        gameBoard.initializeBoard(); // initialize board to text file data
        disp(); // show the board
        play(); // begin game
    }
    /**
     * getter for current board
     * @return the current board
     */
    public Board getBoard() {
        return gameBoard;
    }
    /**
     * method to display the game board
     */
    public void disp() {
        gameBoard.displayBoard();
    }
    /**
     * method to begin the game and run it
     */
    public void play() {
        while(!gameOver) { // while game is not over
            makeMove(); // prompt for move
            disp(); // display board after each move
            gameOver = true; // debug, stop to check moves
            /**
             * this is where priority would be passed
             * to the AI where it would generate the best move using
             * a minimax tree with ab-pruning. It's not finished unfortunately
             */
        }
    }
    /**
     * method to prompt user for a move and perform said move
     */
    public void makeMove() {
        boolean validMove = false; // assume move is false
        Scanner read = new Scanner(System.in); // for input
        System.out.println("\nEnter a move. a1b2 means move from a1 to b2.");
        while (!validMove) { // while no valid input put in
            String s = read.nextLine(); // get input from user
            if (validInput(s)) { // check if input is correct format
                if (isValidMove(s)) { // check if move is possible
                    validMove = true;
                }
            } else {
                System.out.println("Bad input."); // let user know its wrong
            }            
        }
    }    
    /**
     * method to check if input is valid
     * @param s the user input string
     * @return truth value whether its valid
     */
    public boolean validInput(String s) {
        if (s.length() == 4) { // length must be 4
            char c1 = s.charAt(0);
            char c2 = s.charAt(1);
            char c3 = s.charAt(2);
            char c4 = s.charAt(3);
            /**
             * the below verifies its alternating chars and integers
             * also within range
             */
            if ((c1 >= 'a' && c1 <= 'h')
            && (c2 >= '1' && c2 <= '8')
            && (c3 >= 'a' && c3 <= 'h')
            && (c4 >= '1' && c4 <= '8')) {
                return true;
            }
        }
        return false;
    }
    /**
     * method to check if the move is valid, and if so, perform it
     * @param s the input string
     * @return whether its valid or not
     */
    public boolean isValidMove(String s) {
        /**
         * need offsets to compensate, eg. 'a' = 97, etc
         */
        int xCurr = (int)(s.charAt(0) - 97);
        int yCurr = 7-(int)(s.charAt(1) - 49);
        int xDest = (int)(s.charAt(2) - 97);
        int yDest = 7-(int)(s.charAt(3) - 49);
        int[] currPos = {xCurr, yCurr}; // init positions for move
        int[] destPos = {xDest, yDest};
        if (gameBoard.getBoard()[xCurr][yCurr].hasPiece()) { // check if there is a piece
            Piece p = gameBoard.getBoard()[yCurr][xCurr].getPiece(); // get piece data
            char[] c = {s.charAt(0), s.charAt(1), s.charAt(2), s.charAt(3)}; // just for a string later
            String str = "Trying to move "+p.getType()+" from "+c[0]+c[1]+" to "+c[2]+c[3]+"..."; // let user know what its doing
            System.out.println(str); // tell 'em
            if (gameBoard.ownPiece(xCurr, yCurr, WHITE)) { // if you own the piece
               if (gameBoard.isValidMove(currPos, destPos)) { // if the piece can move how you want
                   /**
                    * if you don't own the piece, it can be captured
                    * but also check there is a clear path to the enemy if so
                    */
                   if (!gameBoard.ownPiece(xDest, yDest, WHITE) && gameBoard.isRoom(currPos, destPos, p)) {
                       /**
                        * at this point the move should work
                        */
                       Move m = new Move(yCurr, xCurr, yDest, xDest);
                       gameBoard.move(m); // do the move
                       return true;
                   } else {
                       System.out.println("Path obstructed.");
                   }
               } else {
                   System.out.println("Invalid destination.");
               }
            } else {
                System.out.println("You don't own this piece.");
            }
        } else {
            System.out.println("There is no piece here.");
        }
        return false;
    }
}
