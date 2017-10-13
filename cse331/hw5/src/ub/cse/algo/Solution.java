package ub.cse.algo;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Stack;

public class Solution {

    private HashMap<Integer, ArrayList<Integer>> graph;
    ArrayList<Integer> output = new ArrayList<>();;
    boolean foundCycle = false;



    public Solution(HashMap<Integer, ArrayList<Integer>> graph) {
        this.graph = graph;
    }

    public ArrayList<Integer> findCycle() {
        
        int start = 0;

        dfs(start);

        return output;
    }

    void dfs(int start){
        HashSet<Integer> visited = new HashSet<>();
        Stack<Integer> stack = new Stack<>();

        stack.push(start);

        while(!stack.isEmpty()){
            //pop node
            int current = stack.pop();
            //check if current was visited
            if(!visited.contains(current)){
               //mark visited
                visited.add(current);
                System.out.println(current);


                ArrayList<Integer> adjacencyList = graph.get(current);

                for(int i = adjacencyList.size()-1; i>=0; --i){
                    int node = adjacencyList.get(i);
                    if(!visited.contains(node)){
                        stack.push(node);

                        /*ArrayList<Integer> nodeAdjacencyList = graph.get(node);
                        ArrayList<Integer> startAdjacencyList = graph.get(start);

                        for(int temp : startAdjacencyList){
                            if(nodeAdjacencyList.contains(temp)){
                                foundCycle = true;
                                break;
                            }
                        }*/
                    } 
                }
                
            }
            
            if(foundCycle){
                break;
            }

            
        }

        for(int node : visited){
            if(graph.get(node).size() > 1){
               output.add(node); 
            } else {
               foundCycle = false;
               output = new ArrayList<>();
            }
        }
    }
}

