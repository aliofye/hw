package ub.cse.algo;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.HashMap;

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
        
        Graph input = readFile(inputFilename);
        
        Solution student = new Solution(input.getStartNode(), input.getEndNode(), input.getGraph());
        ArrayList<Integer> studentSolution = student.outputPath();
        
        System.out.println("Your solution:");
        System.out.println("================================================================================");
        System.out.println(studentSolution); 
        System.out.println("================================================================================");
    }


    private static Graph readFile(String inputFilePath) {
        int startNode = 0;
        int endNode = 0;
        HashMap<Integer, ArrayList<Integer>> graph = new HashMap<Integer, ArrayList<Integer>>();
        BufferedReader bufferedReader = null;

        try {
            bufferedReader = new BufferedReader(new FileReader(inputFilePath));
        }
        catch (FileNotFoundException e) {
            System.err.println("Unable to open the file " + inputFilePath);
            e.printStackTrace();
        }

        try {
            startNode = Integer.valueOf(bufferedReader.readLine());
            endNode = Integer.valueOf(bufferedReader.readLine());
            int i = 0;
            String line;
            while((line = bufferedReader.readLine()) != null) {
                ArrayList<Integer> nodes = new ArrayList<>();
                for (String part : line.split("\\s+")) {
                    nodes.add(Integer.valueOf(part));
                }
                graph.put(i, nodes);
                i++;
            }
        }
        catch (IOException e) {
            e.printStackTrace();
        }
        return new Graph(startNode, endNode, graph);
    }
}
