//********************************************************************
//  EvenOdd.java       Author: Lewis/Loftus
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
      int a[] = new int [25];



      do
      {
         numStr = JOptionPane.showInputDialog ("How many numbers in the array: ");

         num = Integer.parseInt(numStr);

         for (int i = 0; i < num; i++)
         {
		   numStr = JOptionPane.showInputDialog ("Enter a[" + i + "] : ");
		   a[i] = Integer.parseInt(numStr);
	     }





         JOptionPane.showMessageDialog (null, "The array you entered follows");

         for (int i = 0; i < num; i++)
         {
			JOptionPane.showMessageDialog (null, a[i]);
	     }

         again = JOptionPane.showConfirmDialog (null, "Do Another?");
      }
      while (again == JOptionPane.YES_OPTION);
   }
}