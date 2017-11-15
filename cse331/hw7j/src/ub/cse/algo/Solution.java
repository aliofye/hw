package ub.cse.algo;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.PriorityQueue;
import java.util.Collections;


public class Solution {
    
    static private ArrayList<Integer> outputPath = new ArrayList<>();
    private int _startNode;
    private int _endNode;
    private HashMap<Integer, ArrayList<Integer>> graph;
    public Solution(int startNode, int endNode, HashMap<Integer, ArrayList<Integer>> g){
        _startNode = startNode;
        _endNode = endNode;
        graph = g;
    }

    class Pair implements Comparable<Pair>{
        int weight;
        int node;

        public Pair(int node, int weight){
            this.node = node;
            this.weight = weight;
        }

        @Override
        public int compareTo(Pair pair) {
           int otherWeight = ((Pair) pair).weight;
           return this.weight - pair.weight;
        }
    }
    
    void createPath(ArrayList<Integer> path, int node){
        if(path.get(node) == -1){
            return;
        }

        createPath(path, path.get(node));

        outputPath.add(path.get(node));

    }

    public ArrayList<Integer> outputPath(){
       
        PriorityQueue<Pair> queue = new PriorityQueue<>();
        HashSet<Integer> visited = new HashSet<>();

        int graphSize = graph.size();

        ArrayList<Integer> minDistance = new ArrayList<Integer>(Collections.nCopies(graphSize, Integer.MAX_VALUE));
        ArrayList<Integer> path = new ArrayList<Integer>(Collections.nCopies(graphSize, -1));

        int startNodeWeight = graph.get(_startNode).get(0);

        queue.add(new Pair(_startNode, startNodeWeight));

        while(queue.peek() != null){
            Pair pair = queue.poll();

            int currentNode = pair.node;
            int currentWeight = pair.weight;

            visited.add(currentNode);

            ArrayList<Integer> adjacencyList = graph.get(currentNode);

            for(int i=1; i<adjacencyList.size(); i++){
                int targetNode = adjacencyList.get(i);
                int targetWeight = graph.get(targetNode).get(0);
            

            
                if(!visited.contains(targetNode)){

                    int distance = currentWeight + targetWeight;
                    if(distance < minDistance.get(targetNode)){    
                        path.set(targetNode, currentNode);
                        minDistance.set(targetNode, distance);
                        queue.add(new Pair(targetNode, distance));
                    }
                }
            }
        }
        
        createPath(path, _endNode);

        if(outputPath.size() != 0){
            outputPath.add(_endNode);
        }

        return outputPath;
    }
}

