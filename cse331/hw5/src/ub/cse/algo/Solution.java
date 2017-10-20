package ub.cse.algo;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;

public class Solution {

    private HashMap<Integer, ArrayList<Integer>> graph;

    boolean foundCycle = false;



    public Solution(HashMap<Integer, ArrayList<Integer>> graph) {
        this.graph = graph;
    }

    public ArrayList<Integer> findCycle() {
        
        HashSet<Integer> visited = new HashSet<>();
        ArrayList<Integer> output = new ArrayList<>();
 
        for(int i = 0; i<graph.size(); ++i){
            if(!foundCycle){
                output = new ArrayList<>();
                visited = new HashSet<>();

                dfs(i,i,visited, output);
                                
            }
        }

        if(!foundCycle){
            output = new ArrayList<>();
        }

        return output;
    }

    void dfs(int n, int goal, HashSet visited, ArrayList<Integer> output){
        
        System.out.println(" ");
        System.out.println("Check: " + n + " " + goal);

        visited.add(n);
        
        output.add(n);
        
        ArrayList<Integer> adj = graph.get(n);
        

        for(int node : adj){
  
            System.out.print(node +  ", ");
 
            if(node == goal && output.size() > 2 && graph.get(node).size() > 1){
                foundCycle = true;
            }
            
            if (!visited.contains(node) && !foundCycle && graph.get(node).size() > 1){    
               dfs(node, goal, visited, output);
            }   
        }
    }
    
}

