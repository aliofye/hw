package ub.cse.algo;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * Wrapper class for objects given to students.
 */
public class PreferenceLists {

    private HashMap<Integer, ArrayList<Integer>> men;
    private HashMap<Integer, ArrayList<Integer>> women;

    public PreferenceLists(HashMap<Integer, ArrayList<Integer>> men,
                           HashMap<Integer, ArrayList<Integer>> women) {
        this.men = men;
        this.women = women;
    }

    /**
     * Get the map containing the men's preference lists
     * 
     * @return map of men's preference list
     */
    public HashMap<Integer, ArrayList<Integer>> getMen() {
        return men;
    }

    /**
     * Get the map containing the women's preference lists
     * 
     * @return map of women's preference list
     */
    public HashMap<Integer, ArrayList<Integer>> getWomen() {
        return women;
    }

    /**
     * With N men and N woman will give N.
     * 
     * @return number of men (equal to number of women)
     */
    public int getSize() {
        return men.size();
    }
}
