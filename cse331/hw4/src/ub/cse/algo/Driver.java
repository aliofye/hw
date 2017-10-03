package ub.cse.algo;

/**
 * Class for running the grader. Will take in a command line argument specifying
 * the number of testcases to run.
 */
public class Driver {

    // The following variables might need to be changed.
    private static String inputFilename;
    private static long studentTime = 0;

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide the number of runs as the argument");
        }
        inputFilename = args[0];
        
        Graph graph = new HW4Utility().readFile(inputFilename);
        
        Integer startNode = graph.getStartNode();
 
        Solution student = new Solution(startNode, graph);
        int[] studentSolution = student.outputDistances();
        
        System.out.println("Your solution:");
        System.out.println("=======================================================================================================");
        if(studentSolution != null){
            System.out.printf("["+studentSolution[0]);
            for(int i=1;i<studentSolution.length;i++){
                System.out.printf(","+studentSolution[i]);
            }
            System.out.println("]");
        } else {
            System.out.println("[]");
        }
        System.out.println("=======================================================================================================");
    }
}
