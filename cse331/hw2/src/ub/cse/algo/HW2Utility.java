package ub.cse.algo;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;

/**
 * Utility class for reading of stable matching problem input files.
 *
 * @param <E> Type of object returned by reading an input file
 */
public class HW2Utility {

    /**
     * Reads the file at the specified location and parses it to get the needed
     * information for the problem.
     * 
     * @param inputFilePath File path for problem input
     * @return Object containing all needed data structures for the problem
     */

    public PreferenceLists readFile(String inputFilePath) {
         HashMap<Integer, ArrayList<Integer>> hospitalList = new HashMap<Integer, ArrayList<Integer>>();
         HashMap<Integer, ArrayList<Integer>> studentList = new HashMap<Integer, ArrayList<Integer>>();
         BufferedReader bufferedReader = null;

        try {
            bufferedReader = new BufferedReader(new FileReader(inputFilePath));
        }
        catch (FileNotFoundException e) {
            System.err.println("Unable to open the file " + inputFilePath);
            e.printStackTrace();
        }

        try {
            int nHospital = Integer.valueOf(bufferedReader.readLine());
            int nStudent = Integer.valueOf(bufferedReader.readLine());

            for (int i = 1; i <= nHospital; i++) {
                ArrayList<Integer> preferences = new ArrayList<>();
                String line = bufferedReader.readLine();
                for (String part : line.split("\\s+")) {
                    preferences.add(Integer.valueOf(part));
                }
                hospitalList.put(i, preferences);
            }
            for (int i = 1; i <= nStudent; i++) {
                ArrayList<Integer> preferences = new ArrayList<>();
                String line = bufferedReader.readLine();
                for (String part : line.split("\\s+")) {
                    preferences.add(Integer.valueOf(part));
                }
                studentList.put(i, preferences);
            }
        }
        catch (IOException e) {
            e.printStackTrace();
        }
        return new PreferenceLists(studentList, hospitalList);
    }

}
