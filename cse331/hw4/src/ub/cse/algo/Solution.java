package ub.cse.algo;

import java.util.ArrayList;
import java.util.HashMap;

public class Solution {
	  private int startNode;
	  private HashMap<Integer, ArrayList<Integer>> graph;
	  public Solution(int node, HashMap<Integer, ArrayList<Integer>> g){
	    startNode = node;
	    graph = g;
	  }

	  public int[] outputDistances(){
	    
	    int n = graph.size();

	    int[] output = new int[n];

	    ArrayList<Integer> edges = new ArrayList<Integer>(graph.get(startNode));

	    //set the distance of starting node to 0
	    output[startNode] = 0;

	    //set the distance of all edges of starting node to 1
	    for(int currentNode : edges){	
	    	output[currentNode] = 1;

	    	//remove the edges of index=currentNode from graph
	    	graph.remove(currentNode);
	    }

	    //remove the edges of index=startNode from graph
	    graph.remove(startNode);

	    
	    //iterate through the remaining graph edges
	    graph.forEach((node, newEdges) -> {
	    	for(int adjacentNode : edges){
	    		if(output[adjacentNode] > 0){
		    		output[node] = output[adjacentNode] + 1;
	    		}
	    	}
	    });



	    return output;  
	}
}
