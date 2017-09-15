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
public class HW1Utility {

    /**
     * Reads the file at the specified location and parses it to get the needed
     * information for the problem.
     * 
     * @param inputFilePath File path for problem input
     * @return Object containing all needed data structures for the problem
     */

    public PreferenceLists readFile(String inputFilePath) {
        HashMap<Integer, ArrayList<Integer>> men = new HashMap<>();
        HashMap<Integer, ArrayList<Integer>> women = new HashMap<>();
        BufferedReader bufferedReader = null;

        try {
            bufferedReader = new BufferedReader(new FileReader(inputFilePath));
        }
        catch (FileNotFoundException e) {
            System.err.println("Unable to open the file " + inputFilePath);
            e.printStackTrace();
        }

        try {
            int numberOfMenAndWomen = Integer.valueOf(bufferedReader.readLine());

            for (int i = 1; i <= numberOfMenAndWomen; i++) {
                ArrayList<Integer> preferences = new ArrayList<>();
                String line = bufferedReader.readLine();
                for (String part : line.split("\\s+")) {
                    preferences.add(Integer.valueOf(part));
                }
                women.put(i, preferences);
            }
            for (int i = 1; i <= numberOfMenAndWomen; i++) {
                ArrayList<Integer> preferences = new ArrayList<>();
                String line = bufferedReader.readLine();
                for (String part : line.split("\\s+")) {
                    preferences.add(Integer.valueOf(part));
                }
                men.put(i, preferences);
            }
        }
        catch (IOException e) {
            e.printStackTrace();
        }
        return new PreferenceLists(men, women);
    }

}
