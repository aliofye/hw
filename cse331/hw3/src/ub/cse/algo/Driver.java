package ub.cse.algo;

import java.util.ArrayList;

/**
 * The driver for homework three. CSE 331
 */
public class Driver {
    
    private static String inputFilename;

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide the filename as a command line argument");
        }
        inputFilename = args[0];
        
        ArrayList<Integer> input = new HW3Utility().readFile(inputFilename);

        
        Solution student = new Solution(input);
        ArrayList<Integer> studentSolution = student.outputVector();
        
        System.out.println("Your solution:");
        System.out.println("=======================================================================================================");
        System.out.println(studentSolution); 
    }
}
