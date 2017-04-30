//********************************************************************
//  ArraySelectionSort.java       Author: Ali Morshid
//
//  Demonstrates the use of the JOptionPane class.
//********************************************************************
/*UML DIAGRAM
Class Name: ArraySelectionSort
Class Variables: String numStrl, int num, again and String string[]
Class Methods: display(display array in the console) and sort(sorts any given array)
*/

import javax.swing.JOptionPane;

public class ArraySelectionSort
{
   //-----------------------------------------------------------------
   //  Determines if the value input by the user is even or odd.
   //  Uses multiple dialog boxes for user interaction.
   //-----------------------------------------------------------------
   public static void main (String[] args)
   {
      String numStr;
      int num, again;
      String string[] = new String [25];//creates the array that will be used



      do//prompts user to input the number of slots in the array that should be used
      {
         numStr = JOptionPane.showInputDialog ("How many strings in the array: ");
		//sets the value of of num throught input by user
         num = Integer.parseInt(numStr);
        //prompts user to input values for the array
         for (int i = 0; i < num; i++)
         {
		   numStr = JOptionPane.showInputDialog ("Enter a[" + i + "] : ");
		   string[i] = numStr;
	     }




		//displays array values
         JOptionPane.showMessageDialog (null, "The array you entered follows");
         for (int i = 0; i < num; i++)
         {
			JOptionPane.showMessageDialog (null, string[i]);
	     }
	     //displays string[] using System.out
	     display(num, string);
		 //sorts string[]
	     sort(num, string);
        //displays the array values sorted
	     JOptionPane.showMessageDialog (null, "The sorted array you entered follows");

		 for (int i = 0; i < num; i++)
		 {
		 	  JOptionPane.showMessageDialog (null, string[i]);
	     }
	     //displays string[] using System.out
	     display(num, string);
		//prompt the user for another run of the program
         again = JOptionPane.showConfirmDialog (null, "Do Another?");
      }
      //checks if the user clicks YES
      while (again == JOptionPane.YES_OPTION);
   }//end do

	//a method to display the array in the command prompt window
	public static void display(int num, String b[])
	{//start display
			 for (int i = 0; i < num; i++)

			 	  System.out.print(b[i] + " ");
			 	  System.out.println();

     }//end display


	//subprogram called to sort the array values in ascending order
   public static void sort(int num, String a[])
   {//start sort
	   // min = position of lowest alphabetical ordered string for each comparison round
	  	         int min;

	  	         // declares a string
	  	         String temp;

	  	         // Outside loop starts from string[0] and goes to next to last string[]
	  	         for (int index = 0; index < num-1; index++)
	  	         {
	  	            // initialize min as the current outside loop position
	  	            min = index;

	  	            // Inside loop goes from 1 more than the starting outside loop string[] to the last string[]
	  	            for (int scan = index+1; scan < num; scan++)

	  	               // compare the strings of the two string[] using String compareTo() method
	  	               if (a[index].compareTo(a[scan])>0)
	  	               {

	  	                  // if the inside loop title is < current minimum title, replace min by inside loop position
	  	                  min = scan;

	  	            // Swap the current outside loop string[] with the one whose title is next in alpah order
	  	                temp = a[min];
	  	                a[min] = a[index];
	                    a[index] = temp;
				      }//end if

			   }//end for

   }//end sort



}//end main