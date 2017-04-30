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
//  4.  quarter
//  5.  dime
//  6.  nickle
//  7.  penny
//
//  UML Diagram
//  Class:  BreakItDown.java
//-----------------------------------------
//  Class Variables:  ten, five, one, quarter, dime, nickle, penny, monAmt, tenDollars, fiveDollars, oneDollars, quarterDollars, dimeDollars, nickleDollars, pennyDollars,tenDollar, fiveDollar, oneDollar, quarterDollar, dimeDollar, nickleDollar, and pennyDollar
//-----------------------------------------
//  Class Methods:  +main(String []):  void, scanner
//********************************************************************
import java.util.Scanner;

public class BreakItDown
{

    public static void main (String[] args)
    {

		final int ten = 10;
		final int five = 5;
		final int one = 1;
		final double quarter = 0.25;
		final double dime = 0.10;
		final double nickle = 0.05;
		final double penny = 0.01;
		double monAmt;
		double tenDollars;
		double fiveDollars;
		double oneDollars;
		double quarterDollars;
		double dimeDollars;
		double nickleDollars;
		double pennyDollars;
	    double tenDollar;
		double fiveDollar;
		double oneDollar;
		double quarterDollar;
		double dimeDollar;
		double nickleDollar;
		double pennyDollar;


        Scanner scan = new Scanner (System.in);
		        System.out.println ("Enter the number you want to break down:");
        monAmt = scan.nextDouble();
//Equation to find the remainder of the amount inputted by the user, then substracting the total by the amount inputted by the user and then dividing it by 10 and the pattern continues from here.
        tenDollar = monAmt % ten;
        tenDollars = (monAmt - tenDollar) / ten;
		System.out.println (tenDollars + "\tTen Dollar Bill(s)");

		fiveDollar = tenDollar % five;
		fiveDollars = (tenDollar - fiveDollar) / five;
		System.out.println (fiveDollars + "\tFive Dollar Bill(s)");

		oneDollar = fiveDollar % one;
		oneDollars = (fiveDollar - oneDollar) / one;
		System.out.println (oneDollars + "\tOne Dollar Bill(s)");

		quarterDollar = oneDollar % quarter;
		quarterDollars = (oneDollar - quarterDollar) / quarter;
		System.out.println (quarterDollars + "\tQuarter(s)");

		dimeDollar = quarterDollar % dime;
		dimeDollars = (quarterDollar - dimeDollar) / dime;
		System.out.println (dimeDollars + "\tDime(s)");

		nickleDollar = dimeDollar % nickle;
		nickleDollars = (dimeDollar - nickleDollar) / nickle;
		System.out.println (nickleDollars + "\tNickle(s)");
//added 1 to the equation bellow to offset the shortage in every monetary amount inputted in the penny section.
		pennyDollar = nickleDollar % penny;
		pennyDollars =((nickleDollar - pennyDollar) / penny +1);
		System.out.println (pennyDollars + "\tPenny(ies)");





    }
}

/* Output
Enter the number you want to break down:
47.63
4.0     Ten Dollar Bill(s)
1.0     Five Dollar Bill(s)
2.0     One Dollar Bill(s)
2.0     Quarter(s)
1.0     Dime(s)
0.0     Nickle(s)
3.0     Penny(ies)
Press any key to continue . . .

*/

//change= 100 * money;
//ten = change / 1000;
//change = change % 1000;
//fives = change / 500;
//change = change % 500;