package ub.cse.algo;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * Wrapper class for objects given to students.
 */
public class Graph {
    
    private HashMap<Integer, ArrayList<Integer>> graph;
    int startNode, endNode;
    
    public Graph(int startNode, int endNode,
                 HashMap<Integer, ArrayList<Integer>> graph) {
        this.startNode = startNode;
        this.endNode = endNode;
        this.graph = graph;
    }
    
    /**
     * Get the start node of the graph
     */
    public int getStartNode() {
        return startNode;
    }
    
    /**
     * Get the end node of the graph
     */
    public int getEndNode() {
        return endNode;
    }
    
    /**
     * Get the graph
     */
    public HashMap<Integer, ArrayList<Integer>> getGraph() {
        return graph;
    }
}


