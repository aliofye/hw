package ub.cse.algo;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * Wrapper class for objects given to students.
 */
public class PreferenceLists {
    
    private HashMap<Integer, ArrayList<Integer>> students;
    private HashMap<Integer, ArrayList<Integer>> hospitals;
    
    public PreferenceLists(HashMap<Integer, ArrayList<Integer>> students,
                           HashMap<Integer, ArrayList<Integer>> hospitals) {
        this.students = students;
        this.hospitals = hospitals;
    }
    
    /**
     * Get the map containing the student's preference lists
     *
     * @return map of student's preference list
     */
    public HashMap<Integer, ArrayList<Integer>> getStudents() {
        return students;
    }
    
    /**
     * Get the map containing the hospital' preference lists
     *
     * @return map of hospital's preference list
     */
    public HashMap<Integer, ArrayList<Integer>> getHospitals() {
        return hospitals;
    }
}

