//********************************************************************
//  TempConverter.java       Author: Lewis/Loftus
//  Reprogrammed by Ali Morshid
//
//  Demonstrates the use of primitive data types and arithmetic
//  expressions.
//   1. Prompt user to input a fahrenheit temperature.
//   2. get user input.
//   3. use the conversion formula below using the user input to calculate Celsius value.
//	 4. Display results of conversion.
//********************************************************************

import java.util.Scanner;

public class TempConverter
{
    //-----------------------------------------------------------------
    //  Computes the Celsius equivalent of a specific Fahrenheit
    //  value using the formula C = 5/9 (F-32)
    //-----------------------------------------------------------------
    public static void main (String[] args)

    {
        final int BASE = 32;
        final double CONVERSION_FACTOR = 5.0 / 9.0;

        double celsiusTemp;
        int fahrenheitTemp;  // value to convert

        Scanner scan = new Scanner (System.in);
        System.out.println ("Enter the number in Fahrenheit that you want to convert to Celsius:");
        fahrenheitTemp = scan.nextInt();



        celsiusTemp = CONVERSION_FACTOR * (fahrenheitTemp - BASE);


        System.out.println ("Celsius Temperature: " + celsiusTemp);

    }
}

/*    OUTPUT
Enter the number in Fahrenheit that you want to convert to Celsius:
32
Celsius Temperature: 0.0
Press any key to continue . . .

*/

/*    OUTPUT2
Enter the number in Fahrenheit that you want to convert to Celsius:
212
Celsius Temperature: 100.0
Press any key to continue . . .
*/

/*    OUTPUT3
Enter the number in Fahrenheit that you want to convert to Celsius:
-40
Celsius Temperature: -40.0
Press any key to continue . . .

*/
