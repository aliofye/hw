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
public class HW4Utility {

    /**
     * Reads the file at the specified location and parses it to get the needed
     * information for the problem.
     * 
     * @param inputFilePath File path for problem input
     * @return Object containing all needed data structures for the problem
     */
    public Graph readFile(String inputFilePath) {
    	Integer startNode;
        Graph graph = null;
        BufferedReader bufferedReader = null;

        try {
            bufferedReader = new BufferedReader(new FileReader(inputFilePath));
        }
        catch (FileNotFoundException e) {
            System.err.println("Unable to open the file " + inputFilePath);
            e.printStackTrace();
        }

        try{
            startNode = Integer.valueOf(bufferedReader.readLine());
            graph = new Graph(startNode);
            graph.setStartNode(startNode);
            String line = null;
            Integer node = 0;
            while((line = bufferedReader.readLine()) != null) {
                graph.put(node, new ArrayList<Integer>());
                String[] parts = line.trim().split("\\s+");
                for(String neighbor : parts){
                  Integer n = Integer.parseInt(neighbor);
                  graph.get(node).add(n);
                }
                node++;
            }

        }
        catch (IOException e) {
            e.printStackTrace();
        }
        return graph;
    }

}
