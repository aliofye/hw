


//********************************************************************
//  StarTriangle.java       Author: Ali Morshid
//
//  Demonstrates the use of nested for loops.
//********************************************************************
import java.util.Scanner;
public class StarTriangle

{
   //-----------------------------------------------------------------
   //  Prints a triangle shape using asterisk (star) characters.
   //-----------------------------------------------------------------
   public static void main (String[] args)
   {
      final int MAX_ROWS = 10;
      int choice = 0;



      for (int row = 1; row <= MAX_ROWS; row++)//loop for amount of rows to be displayed
      {


		 for (int space = 1; space <= 10-row ; space++)//loop to display the correct shape desired
              System.out.print(" ");

		 for (int star = 1; star <= row; star++)//loop to display the stars
			  System.out.print ("*");

		 for (int star = 2; star <= row; star++)
		 	  System.out.print ("*");

         System.out.println();




      }

   }
}





/* Output 2
         *
        ***
       *****
      *******
     *********
    ***********
   *************
  ***************
 *****************
*******************
*/

