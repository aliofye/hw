package ub.cse.algo;

import java.util.ArrayList;
import java.util.HashMap;

/**
* Graph data structure to return multiple data structures for Homework 10
*/

public class Graph {

    private int origin;
    private ArrayList<HashMap<Integer, Integer>> incoming_edges;
    private ArrayList<HashMap<Integer, Integer>> outgoing_edges;

    public Graph(int origin, ArrayList<HashMap<Integer, Integer>> incoming_edges, ArrayList<HashMap<Integer, Integer>> outgoing_edges) {
        this.origin = origin;
        this.incoming_edges = incoming_edges;
        this.outgoing_edges = outgoing_edges;
    }

    public int getOrigin() {
        return this.origin;
    }

    public ArrayList<HashMap<Integer, Integer>> getIncomingEdges() {
        return this.incoming_edges;
    }

    public ArrayList<HashMap<Integer, Integer>> getOutgoingEdges() {
        return this.outgoing_edges;
    }
}
