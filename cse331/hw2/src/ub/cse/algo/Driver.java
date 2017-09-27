package ub.cse.algo;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * The driver for homework two. CSE 331
 */
public class Driver {
    
    // The following variables might need to be changed.
    private static String inputFilename;
    private static long studentTime = 0;

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide the number of runs as the argument");
        }
        inputFilename = args[0];
        
        PreferenceLists prefLists = new HW2Utility().readFile(inputFilename);
        
        HashMap<Integer, ArrayList<Integer>> students = prefLists.getStudents();
        HashMap<Integer, ArrayList<Integer>> hospitals = prefLists.getHospitals();
        
        Solution student = new Solution(hospitals.size(), students.size(), hospitals, students);
        ArrayList<Match> studentSolution = student.getMatches();
        
        System.out.println("Your solution:");
        System.out.println("=======================================================================================================");
        System.out.println(studentSolution); System.out.println("=======================================================================================================");
    }
}
