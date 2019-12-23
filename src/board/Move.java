package board;

/**
 * Move class
 * @author Robert Scott, 4582342
 */
public class Move {
    private int curr[], dest[]; // position of before- and after-move
    /**
     * Move constructor
     * @param xa x coord of old position
     * @param ya y coord of old position
     * @param xb x of new
     * @param yb y of new
     */
    public Move(int xa, int ya, int xb, int yb) {
        curr = new int[2];
        dest = new int[2];
        curr[0] = xa;
        curr[1] = ya;
        dest[0] = xb;
        dest[1] = yb;        
    }
    /**
     * setter method for old position
     * @param x new old x
     * @param y new old y
     */
    public void setCurr(int x, int y) {
        curr[0] = x;
        curr[1] = y;
    }
    /**
     * setting method for new position
     * @param x new new x
     * @param y new new y
     */
    public void setDest(int x, int y) {
        dest[0] = x;
        dest[1] = y;
    }
    /**
     * getter method for old position
     * @return old position
     */
    public int[] getCurr() {
        return curr;
    }
    /**
     * getting method for new position
     * @return new position
     */
    public int[] getDest() {
        return dest;
    }
}
