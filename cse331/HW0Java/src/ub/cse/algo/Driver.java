package ub.cse.algo;

import java.util.List;
/**
 * Class for running hw0. Will take in a command line argument specifying
 * the number of testcases to run.
 */
public class Driver {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide the testcase filepath as the argument");
        }
        HW0Utility utility = new HW0Utility();
        List<String> l = utility.readFile(args[0]);
        Solution s = new Solution(l);
        s.outputSortedList("A","B",l.size());
    }
}
