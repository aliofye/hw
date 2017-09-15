package ub.cse.algo;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;

/**
 * The driver for homework one. CSE 331
 */
public class Driver {

    // The following variables might need to be changed.
    private static String inputFilename;
    private static long studentTime = 0;

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Please provide the input filepath as the first argument");
            return;
        }

        inputFilename = args[0];

        PreferenceLists prefLists = new HW1Utility().readFile(inputFilename);

        HashMap<Integer, ArrayList<Integer>> men = prefLists.getMen();
        HashMap<Integer, ArrayList<Integer>> women = prefLists.getWomen();

        Solution student = new Solution(men.size(), men, women);
        ArrayList<Matching> studentSolution = student.outputStableMatchings();

        Collections.sort(studentSolution);
        System.out.println("Your solution:");
        System.out.println("=======================================================================================================");
        System.out.println(studentSolution.size());
        for (ArrayList<Marriage> match : studentSolution) {
            System.out.println(match.toString());
            System.out.println("=======================================================================================================");

        }
    }

}
