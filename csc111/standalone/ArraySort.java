//********************************************************************
//  ArraySort.java       Author: Lewis/Loftus
//
//  Demonstrates the use of the JOptionPane class.
//********************************************************************

import javax.swing.JOptionPane;

public class ArraySort
{
   //-----------------------------------------------------------------
   //  Determines if the value input by the user is even or odd.
   //  Uses multiple dialog boxes for user interaction.
   //-----------------------------------------------------------------
   public static void main (String[] args)
   {
      String numStr;
      int num, again;
      String a[] = new String [25];//creates the array that will be used



      do//prompts user to input the number of slots in the array that should be used
      {
         numStr = JOptionPane.showInputDialog ("How many strings in the array: ");

         num = Integer.parseInt(numStr);

         for (int i = 0; i < num; i++)//prompts user to input values for the array
         {
		   numStr = JOptionPane.showInputDialog ("Enter a[" + i + "] : ");
		   a[i] = Integer.parseInt(numStr);
	     }





         JOptionPane.showMessageDialog (null, "The array you entered follows");//displays array values

         for (int i = 0; i < num; i++)
         {
			JOptionPane.showMessageDialog (null, a[i]);
	     }

	    /*public consoleDisplay()
	    {
	     	for (int i = 0; i < num; i++)
	     	{
				System.out.println(a[i]);
	     	}
	    }*/

	     sort(num, a);

	     JOptionPane.showMessageDialog (null, "The sorted array you entered follows");//displays the array values sorted

		 for (int i = 0; i < num; i++)
		 {
		 	  JOptionPane.showMessageDialog (null, a[i]);
	     }

         again = JOptionPane.showConfirmDialog (null, "Do Another?");
      }
      while (again == JOptionPane.YES_OPTION);
   }
   public static void sort(int num, int a[])//subprogram called to sort the array values in ascending order
   {//start sort
	   int temp;
	   for (int i = 0; i < num-1; i++)
	       for (int j = i+1; j < num; j++)
	       	   if (a[i] > a[j])
	       	   {
				   temp = a[i];
				   a[i] = a[j];
				   a[j] = temp;
		       }
   }//end sort

  }//end main