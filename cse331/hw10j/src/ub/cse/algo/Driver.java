package ub.cse.algo;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Arrays;

import java.io.IOException;
import java.io.FileNotFoundException;

/**
 * Class for running the grader. Will take in a command line argument specifying
 * the number of testcases to run.
 */
public class Driver {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide the testcase filename as a command line argument");
        }
        String inputFilename = args[0];

        Graph input = read_file(inputFilename);

        Solution student = new Solution(input.getOrigin(),
                                        input.getIncomingEdges(),
                                        input.getOutgoingEdges());
        int[] min_distance = student.outputShortestDistance();

        System.out.println("Your solution:");
        System.out.println("================================================================================");
        System.out.println(Arrays.toString(min_distance));
        System.out.println("================================================================================");
    }


    public static Graph read_file(String inputFilePath){
        int origin = 0;
        ArrayList<HashMap<Integer, Integer>> incoming_edges = new ArrayList<HashMap<Integer, Integer>>();
        ArrayList<HashMap<Integer, Integer>> outgoing_edges = new ArrayList<HashMap<Integer, Integer>>();
        BufferedReader reader = null;

        try {
            reader = new BufferedReader(new FileReader(inputFilePath));
            origin = Integer.valueOf(reader.readLine());
            String line = "";
            while ((line = reader.readLine()) != null) {
                HashMap<Integer, Integer> incoming = new HashMap<>();
                String[] parts = line.split("\\s+");
                for (int i = 0; i < parts.length; i += 2) {
                    incoming.put(Integer.valueOf(parts[i]), Integer.valueOf(parts[i + 1]));
                }
                HashMap<Integer, Integer> outgoing = new HashMap<>();
                parts = reader.readLine().split("\\s+");
                for (int i = 0; i < parts.length; i += 2) {
                    outgoing.put(Integer.valueOf(parts[i]), Integer.valueOf(parts[i + 1]));
                }
                incoming_edges.add(incoming);
                outgoing_edges.add(outgoing);
            }
            reader.close();

          } catch (FileNotFoundException e) {
              System.err.println("Unable to open the file " + inputFilePath);
              e.printStackTrace();
          } catch (IOException e) {
              e.printStackTrace();
          } catch (NullPointerException e) {
              e.printStackTrace();
          }
          return new Graph(origin, incoming_edges, outgoing_edges);
    }
}
