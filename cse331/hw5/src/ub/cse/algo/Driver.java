package ub.cse.algo;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.HashMap;

/**
 * The driver for homework one. CSE 331
 */
public class Driver {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Please provide the input filepath as the first argument");
            return;
        }

        String inputFilename = args[0];

        HashMap<Integer, ArrayList<Integer>> adjLists = readFile(inputFilename);

        Solution student = new Solution(adjLists);

        ArrayList<Integer> studentSolution = student.findCycle();

        System.out.println("Your solution:");
        System.out.println("=======================================================================================================");
        System.out.println(studentSolution.toString());
        System.out.println("=======================================================================================================");
    }
    
    private static HashMap<Integer, ArrayList<Integer>> readFile(String inFileName) {
        HashMap<Integer, ArrayList<Integer>> adjacencyList = new HashMap<>();
        try {
            BufferedReader bufferedReader = new BufferedReader(new FileReader(inFileName));

            String line = "";
            for (int node = 0; (line = bufferedReader.readLine()) != null; node++) {
                adjacencyList.put(node, new ArrayList<Integer>());
                String[] adjacentFromNode = line.trim().split("\\s+");
                for (String edgeStr : adjacentFromNode) {
                    int edge = Integer.parseInt(edgeStr);
                    adjacencyList.get(node).add(edge);
                }
            }
            bufferedReader.close();
        }
        catch (Exception e) {
            e.printStackTrace();
        }
        return adjacencyList;
    }
}
