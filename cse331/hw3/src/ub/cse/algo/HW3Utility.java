package ub.cse.algo;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

/**
* Utility class for reading of stable matching problem input files.
*
* @param <E> Type of object returned by reading an input file
*/
public class HW3Utility {

  /**
  * Reads the file at the specified location and parses it to get the needed
  * information for the problem.
  *
  * @param inputFilePath File path for problem input
  * @return Object containing all needed data structures for the problem
  */

  public ArrayList<Integer> readFile(String inputFilePath) {
    ArrayList<Integer> vector = new ArrayList<>();

    try{
      BufferedReader bufferedReader = new BufferedReader(new FileReader(inputFilePath));

      int n = Integer.parseInt(bufferedReader.readLine());

      for (int i = 0; i < n; i ++) {
        vector.add(Integer.parseInt(bufferedReader.readLine()));
      }
      bufferedReader.close();

    }
    catch (Exception e) {
      e.printStackTrace();
    }
    return vector;
  }

}
