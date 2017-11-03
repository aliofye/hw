package ub.cse.algo;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;

/**
 * Class for running the grader. Will take in a command line argument specifying
 * the number of testcases to run.
 */
public class Driver {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide the number of runs as the argument");
        }

	    String inputFilename = args[0];
        ArrayList<int[]> listOfRallies = readFile(inputFilename);        
        
        Solution student = new Solution(listOfRallies.size(), listOfRallies);
        ArrayList<int[]> studentSolution = student.getSchedule();
	
        System.out.println("Your solution:");
        System.out.println("=======================================================================================================");
        System.out.print("[");        
        for (int i = 0; i < studentSolution.size(); i++) {            
            System.out.print("(" + studentSolution.get(i)[0] + "," + studentSolution.get(i)[1]+")");
            if (i < studentSolution.size() - 1) {
                System.out.print(", ");
            }
        }
        System.out.print("]");
        System.out.println("=======================================================================================================");
  
    }

    public static ArrayList<int[]> readFile(String inputFilePath) {
            String numberOfRallies;
            String temp;
            ArrayList<int[]> listOfRallies = new ArrayList<int[]>();
            BufferedReader bufferedReader = null;
            
            try {
                bufferedReader = new BufferedReader(new FileReader(inputFilePath));
            }
            catch (FileNotFoundException e) {
                System.err.println("Unable to open the file " + inputFilePath);
                e.printStackTrace();
            }
            
            try{
                numberOfRallies = bufferedReader.readLine();
                for(int i = 1; i <= Integer.parseInt(numberOfRallies); i++){
                    temp = bufferedReader.readLine();
                    String[] rallyInString = temp.split("\\s+");
                    int[] rally = new int[2];
                    rally[0] = Integer.parseInt(rallyInString[0]);
                    rally[1] = Integer.parseInt(rallyInString[1]);
                    listOfRallies.add(rally);
                }
            }
            catch (IOException e) {
                e.printStackTrace();
            }
            
            return listOfRallies;
     }
}
