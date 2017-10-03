package ub.cse.algo;

import java.util.ArrayList;
import java.util.HashMap;

@SuppressWarnings("serial")
public class Graph extends HashMap<Integer, ArrayList<Integer>>{
	private Integer startNode;
	
	public Graph(Integer startNode) {
		this.setStartNode(startNode);
	}

	public Integer getStartNode() {
		return startNode;
	}

	public void setStartNode(Integer startNode) {
		this.startNode = startNode;
	}
}
