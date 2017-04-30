


//********************************************************************
//  DieTossCounter.java       Author: Ali Morshid
//
//
//********************************************************************
import java.util.Scanner;
public class DieTossCounter

{


   public static void main (String[] args)
   {

		int count[] = new int [7];//creates an array
		int r;
		for (int i=0; i < 6; i++){//start for
   	    	 count[i] = 0;
   	    	for (int num=1; num <= 1000; num++)//loop for number of dice rolls
		   			{//start for2
					r = (int)(Math.random() * 7)+1;


					switch(r)//switches face values
					{
				    	case 0:
				      	    count[0]++;
				      	    break;
				    	case 1:
						    count[1]++;
				    	    break;
				    	case 2:
						    count[2]++;
						    break;
						case 3:
							count[3]++;
				    	    break;
				    	case 4:
				    	    count[4]++;
				    	    break;
				    	case 5:
				    	    count[5]++;
				    	    break;
				    	case 6:
				    	    count[6]++;



					}
			}//end for2

	    }//end for
	    for(int c = 1; c < 7; c++)//prints results
					{
					   System.out.println("Face value " + ((c-1)+1) + " = " + count[c]);

	    			}
   }

}


