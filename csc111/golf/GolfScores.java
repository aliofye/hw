

//********************************************************************
//  GolfScores.java       Author: Morshid, Ali
//
//  Demonstrates the use of Scanner to read file input and parse it
//  using alternative delimiters.
//********************************************************************

import java.util.Scanner;
import java.io.*;

public class GolfScores
{
   //-----------------------------------------------------------------
   //  Reads par and scores of 4 golfers for each of the 18 holes.
   //-----------------------------------------------------------------
   public static void main (String[] args) throws IOException
   {
      String scores;
      Scanner fileScan, scoresScan;
      int count = 0, position;
      int score;
      int total[] = new int [5];

      for (int i = 0; i<5; i++)
      	  total[i] = 0;

      fileScan = new Scanner (new File("golf.txt"));

      // Read and process each line of the file
      while (fileScan.hasNext())
      {
         scores = fileScan.nextLine();
         count++;
         System.out.println ("Hole: " + count + " - " + scores);


         scoresScan = new Scanner (scores);
         //scoresScan.useDelimiter(" ");

         //  Print par and each part of the scores
         position = 0;
         while (scoresScan.hasNext())
         {
            score = scoresScan.nextInt();
            total[position] = total[position]+score;
            position++;


	     }

         System.out.println();

         //display the scores: par, player 1-4
         System.out.println("Course Par = " + total[0]);
         System.out.println("Player = " + total[1] + " " + (total[1] - total[0]));
         System.out.println("Player = " + total[2] + " " + (total[2] - total[0]));
         System.out.println("Player = " + total[3] + " " + (total[3] - total[0]));
         System.out.println("Player = " + total[4] + " " + (total[4] - total[0]));
         System.out.println("-------------------------");
      }
   }
}



