package ub.cse.algo;

import java.util.ArrayList;
import java.util.Collections;
import java.lang.Exception.*;

public class Solution {
    
    private int _n_rallies;
    private ArrayList<int[]> _rallies;
    
    public Solution (int n_rallies, ArrayList<int[]> rallies){
        _n_rallies = n_rallies;
        _rallies = rallies;
    }
    
    class Interval implements Comparable<Interval>{
        int id;
        int duration;
        int deadline;

        public Interval(){
            //empty constructor
        }

        public Interval(int id, int duration, int deadline){
            this.id = id;
            this.duration = duration;
            this.deadline = deadline;
        }

        public int compareTo(Interval compareIntervals) {

            int otherDeadline = ((Interval) compareIntervals).deadline;

            //ascending order
            return this.deadline - otherDeadline;
        }
    }
    /**
     * You should fill this in on your own. Rallies is list of tuples, in the form (rally duration, rally deadline).
     * Your output should also be a list of tuples, of the form (rally id, start time of rally). If no possible
     * schedule exists, you should return an empty list.
     * @return
     */
    public ArrayList<int[]> getSchedule(){
        ArrayList<int[]> schedule = new ArrayList<int[]>();

        ArrayList<Interval> ordered_rallies = new ArrayList<Interval>();
        //convert to arraylist of class interval
        for(int i=0; i< _n_rallies; i++){
            Interval interval = new Interval(i, _rallies.get(i)[0], _rallies.get(i)[1]);
            ordered_rallies.add(interval);
        }

        //sort based on deadlines
        Collections.sort(ordered_rallies);

        int start = 0;
        int endIndex = _n_rallies-1;
        int end = ordered_rallies.get(endIndex).deadline;

        for(int i=0; i<_n_rallies; i++){
            Interval interval = ordered_rallies.get(i);
            
            int pair[] = new int[2];
            pair[0] = interval.id;
            pair[1] = start;

            schedule.add(pair);
            start+=interval.duration;

            if(start > end){
                schedule = new ArrayList<>();
                return schedule;
            }

        }

        return schedule;
    }
}
