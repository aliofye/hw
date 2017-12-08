package ub.cse.algo;

import java.util.ArrayList;
import java.util.HashMap;

public class Solution {

    private int origin;
    private ArrayList<HashMap<Integer, Integer>> incoming_edges;
    private ArrayList<HashMap<Integer, Integer>> outgoing_edges;

    public Solution(int origin, ArrayList<HashMap<Integer, Integer>> incoming_edges, ArrayList<HashMap<Integer, Integer>> outgoing_edges){
        this.origin = origin;
        this.incoming_edges = incoming_edges;
        this.outgoing_edges = outgoing_edges;
    }

    class Edge{
        int u;
        int v;
        int w;
        
        public Edge(int u, int v, int w){
            this.u = u;
            this.v = v;
            this.w = w;
        }
    }

    public int[] outputShortestDistance(){
        
        ArrayList<Edge> edges = new ArrayList<>();

        for(int i=0; i<outgoing_edges.size(); i++){
            for(int j=0; j<outgoing_edges.get(i).size(); j++){
                int u = i;
                int v = j;
                
                int w1;
                int w2;

                try{
                    w1 = outgoing_edges.get(u).get(v);  
                    Edge edge1 = new Edge(u,v,w1);
                    edges.add(edge1);
                } catch(NullPointerException e){}

                try{
                    w2 = incoming_edges.get(u).get(v); 
                    Edge edge2 = new Edge(v,u,w2); 
                    edges.add(edge2);  
                } catch(NullPointerException e){}

            }
        }

        final int V = outgoing_edges.size();
        int distance[] = new int[V];

        for(int i=0; i<V; i++){
            distance[i] = Integer.MAX_VALUE;
        }

        distance[origin] = 0;

        //iterate |V-1| times and find shortest path
        for(int i=1; i<=(V-1); i++){  
            
            for(Edge edge : edges){
                
                int u = edge.u;
                int v = edge.v;
                int w = edge.w;
                
                if(w != 0 && distance[u] != Integer.MAX_VALUE && distance[u] + w < distance[v] ){
                   distance[v] = distance[u] + w;
                }
            }
            
        }

        return distance;
    }
}
