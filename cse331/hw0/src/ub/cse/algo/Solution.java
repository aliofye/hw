package ub.cse.algo;

import java.util.List;
import java.util.LinkedList;

public class Solution {
    private List<String> _inputList;
    public Solution(List<String> list){
        _inputList = list;
    }

    public List<String> outputSortedList(String a, String b, int n){
    	LinkedList<String> sortedList = new LinkedList<>();
        
    	for(String input : _inputList){
    		if(input.charAt(0) == a.charAt(0)){
    			sortedList.addFirst(input);
    		} else {
    			sortedList.addLast(input);
    		}
    	}

        return sortedList;
    }

    
}
