//********************************************************************
//  Program Name:  BreakItDown.java
//  Author: Ali Morshid
//  Description:  Breaks down a certain amount of money inputted by user into $ bills and coins.
//
//  Program Logic
//  Display the following
//  1.  ten dollar bills
//  2.  five dollar bills
//  3.  one dollar bills
//  4.  Email Address
//  5.  Major
//  6.  Previous Computer Experience/Courses
//  7.  Employer
//
//  UML Diagram
//  Class:  BreakItDown.java
//-----------------------------------------
//  Class Variables:  none
//-----------------------------------------
//  Class Methods:  +main(String []):  void
//********************************************************************
import java.util.Scanner;

public class BreakItDown
{

    public static void main (String[] args)
    {
		int ten = 10;
		int five = 5;
		int one = 1;
		double quarter = 0.25;
		double dime = 0.10;
		double nickle = 0.05;
		double penny = 0.01;
		double monAmt;
		double brokenDown;

        Scanner scan = new Scanner (System.in);
		        System.out.println ("Enter the number you want to break down:");
        monAmt = scan.nextInt();
        brokenDown = monAmt / ten + five + one + quarter + dime + nickle + penny;

        System.out.println ("The number broken down: " + brokenDown);
    }
}

/* Output
Name:  Ali Morshid
Address:  207 Craton St
Phone Number:  315-440-5291
Email Address:  bl3a5ck@gmail.com
Major:  Computer Science
Previous Computer Experience/Courses: Self taught
Employer:  N/A


*/