package ub.cse.algo;

/**
 * For use in CSE 331. This is a convenient class used to organize pairings. The
 * output of your hw will be an ArrayList of Matches.
 *
 * You can access the man or woman of a marriage by calling marriage._man, or
 * marriage._woman
 */
public class Match implements Comparable<Match>{
    public Integer student;
    public Integer hospital;
    
    Match(Integer hospital, Integer student) {
        this.student = student;
        this.hospital = hospital;
    }
    
    @Override
    public boolean equals(Object obj) {
        Match compare = (Match) obj;
        return (student.equals(compare.student)) && (hospital.equals(compare.hospital));
    }
    
    @Override
    public String toString() {
        return "(" + hospital + ", " + student + ")";
    }
    
    @Override
    public int compareTo(Match other) {
        return this.hospital.compareTo(other.hospital);
    }
}

