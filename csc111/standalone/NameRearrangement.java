//********************************************************************
//  Program Name:  NameRearrangement.java
//  Author: Ali Morshid
//  Description:Rearranges a full name in the following format: First Last, to this following format: Last, First.
//
//  Program Logic
//  Display the following
//  1.Ask for a name input from the user. First, ask for first name. Next, ask for last name.
//  2.Rearrange the name to this format: Last, First
//  3.Display results.
//
//  UML Diagram
//  Class:  NameRearrangement.java
//-----------------------------------------
//  Class Variables: first,last
//-----------------------------------------
//  Class Methods:  +main(String []):  void, Scanner
//********************************************************************

import java.util.Scanner;
public class NameRearrangement
{

    public static void main (String[] args)
    {

		String first;
		String last;
		String reArrange;

		Scanner scan = new Scanner (System.in);
		System.out.println (" Welcome! to rearrange your first name and last name please follow the \n instructions below!");
		System.out.println ("Enter your first name:");
		first = scan.nextLine ();

		System.out.println ("Enter your last name:");
		last = scan.nextLine ();


		reArrange = last.concat (", " +first);
		System.out.println ("Your name rearranged: " + reArrange + ".");







    }
}

/* Output
 Welcome! to rearrange your first name and last name please follow the
 instructions below!
Enter your first name:
Ali
Enter your last name:
Morshid
Your name rearranged: Morshid, Ali.
Press any key to continue . . .

*/
