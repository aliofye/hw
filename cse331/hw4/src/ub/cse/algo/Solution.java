package ub.cse.algo;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Arrays;

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
	    
	    Arrays.fill(output, -1);

	    Queue queue = new LinkedList<>();
	    HashSet<Integer> checked = new HashSet<>();

	    queue.add(startNode);
	    checked.add(startNode);
	    output[startNode] = 0;



	    while(!queue.isEmpty()){
	    	int node = (int) queue.remove();

	    	//set all nodes outputs to be -1, they will be changed if they are connected
	
    		ArrayList<Integer> edges = graph.get(node);
    		
    		for(int adjacentNode : edges){
    			if(!checked.contains(adjacentNode)){
    				
    				queue.add(adjacentNode);
    				checked.add(adjacentNode);

    				//do something here
					if(node == startNode){
						output[adjacentNode] = 1;
					} else {
						output[adjacentNode] = output[node] + 1;
					}			
    			}
    		}

	    }

	    return output;  
	}
}
