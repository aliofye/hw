package ub.cse.algo;

/**
 * For use in CSE 331. This is a convenient class used to organize pairings. The
 * output of your hw will be an ArrayList of Marriages.
 *
 * You can access the man or woman of a marriage by calling marriage._man, or
 * marriage._woman
 */
public class Marriage implements Comparable<Marriage>{
    public Integer man;
    public Integer woman;

    Marriage(Integer man, Integer woman) {
        this.man = man;
        this.woman = woman;
    }

    @Override
    public boolean equals(Object obj) {
        Marriage compare = (Marriage) obj;
        return (man.equals(compare.man)) && (woman.equals(compare.woman));
    }

    @Override
    public String toString() {
        return "(" + man + ", " + woman + ")";
    }

    @Override
    public int compareTo(Marriage other) {
        return this.woman.compareTo(other.woman);
    }
}
