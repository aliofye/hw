package ub.cse.algo;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;


/**
 * @param <E> Type of object returned by reading an input file
 */
public class HW0Utility {

    /**
     * Reads the file at the specified location and parses it to get the needed
     * information for the problem.
     *
     * @param inputFilePath File path for problem input
     * @return Object containing all needed data structures for the problem
     */
    public List<String> readFile(String inputFilePath) {
        String line;
        List<String> inputList = new ArrayList<String>();
        BufferedReader bufferedReader = null;

        try {
            bufferedReader = new BufferedReader(new FileReader(inputFilePath));
        }
        catch (FileNotFoundException e) {
            System.err.println("Unable to open the file " + inputFilePath);
            e.printStackTrace();
        }

        try{
            line = bufferedReader.readLine();
            inputList = Arrays.asList(line.split(","));
        }
        catch (IOException e) {
            e.printStackTrace();
        }

        return inputList;
    }

}
