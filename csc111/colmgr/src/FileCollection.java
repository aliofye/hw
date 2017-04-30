

//********************************************************************
//  FileCollection.java       Author: Ali Morshid
//
//  Represents a collection of FILES.
//********************************************************************

import java.text.NumberFormat;
import java.io.*;
import java.util.Scanner;

/**
 *
 * @author Ali Morshid
 */
public class FileCollection
{
   private FILE[] collection;
   private int count;
   private int currentSize;
   private double totalCost;

   //-----------------------------------------------------------------
   //  Constructor: Creates an initially empty collection.
   //-----------------------------------------------------------------
    /**
     *
     */
    public FileCollection ()
   {
      collection = new FILE[100];
      count = 0;
      totalCost = 0.0;
      currentSize = 100;
   }

   //-----------------------------------------------------------------
   //  Adds a FILE to the collection, increasing the size of the
   //  collection array if necessary.
   //-----------------------------------------------------------------
    /**
     *
     * @param title
     * @param director
     * @param year
     * @param cost
     * @param bluRay
     */
    public void addFILE (String title, String director, int year,
      double cost, boolean bluRay)
   {
      if (count == collection.length)
         increaseSize();

      collection[count] = new FILE (title, director, year, cost, bluRay);
      totalCost += cost;
      count++;
   }

      //-----------------------------------------------------------------
      //  Deletes a FILE from the collection
      //-----------------------------------------------------------------
    /**
     *
     * @param title
     */
    public void subFILE(String title)
   {
         // j will count the number of FILE's in the newly sized collection
         int j = 0;
         // i will count the current number of FILE's
         int i;
         // create a temporary array of FILE objects
         // which will become the newly sized collection
         FILE [] temp = new FILE[count];

         for(i=0; i<count; i++)
         {
            // look for a match
            if(title.compareTo(collection[i].getTitle()) != 0)
            {
               // if there is no match, copy from the old to the new
               temp[j] = collection[i];
               j++;
            }
            else
            {
               // if there is a match, do not copy from the old to the new
               // but update the total value
               totalCost -= collection[i].getCost();
            }
         }

         // check to see if there was a match and a deletion from the collection
         if (i != j)
         {
             count--;
             collection = temp;
         }


     }//end subFILE


     //-----------------------------------------------------------------
	    //  Updates a FILE from the collection
	    //-----------------------------------------------------------------

	  /**
     *
     * @param title
     * @param director
     * @param year
     * @param cost
     * @param bluRay
     */
    public void updFILE(String title, String director, int year,
      double cost, boolean bluRay)
	  {
	       // i will count the number of FILE's in the collection
	       int i;
	       // flag will tell if a match has been found
	       int flag = 0;
	       // temp will become the new FILE collection
	       FILE [] temp = new FILE[count];

	       for(i=0; i<count; i++)
	       {
	          // look for a match
	          if(title.compareTo(collection[i].getTitle()) != 0)
	          {
	             // if there is no match, copy from the old to the new
	             temp[i] = collection[i];
	          }
	          else
	          {
	             // if there is a match, replace the current FILE
	             // with the updated fields and correct the value
	             temp[i] = new FILE (title, director, year, cost, bluRay);
	             totalCost -= collection[i].getCost();
	             totalCost += cost;
	             // set the flag which indicates a change has happened
	             flag = 1;
	          }
	       }

	       // check if an update has taken place
	       if (flag == 1)
	       {
	           collection = temp;
	       }


     }//end updFILE

        //-------------------------------------------------------------------------
	      //  selection sort used to sort CD objects into alphabetical order by title
	      //-------------------------------------------------------------------------


	 /**
     *
     */
    public void selectionSortByTitle ()
	 {
	         // min = position of lowest alphabetical ordered FILE object for each comparison round
	         int min;

	         // create a temporary FILE object for swaping purposes
	         FILE temp = new FILE();

	         // Outside loop starts from FILE object in positon 0 and goes to next to last CD object
	         for (int index = 0; index < count-1; index++)
	         {
	            // initialize min as the current outside loop position
	            min = index;

	            // Inside loop goes from 1 more than the starting outside loop FILE object to the last FILE object
	            for (int scan = index+1; scan < count; scan++)

	               // compare the titles of the two FILE objects using String compareTo() method
	               if (collection[scan].getTitle().compareTo(collection[min].getTitle())<0)

	                  // if the inside loop title is < current minimum title, replace min by inside loop position
	                  min = scan;

	            // Swap the current outside loop FILE object with the one whose title is next in alpah order
	            temp = collection[min];
	            collection[min] = collection[index];
	            collection[index] = temp;
             }
     }//endselectionSortByTitle

     //-----------------------------------------------------------------------------
	 //  insertion sort used to sort an integer array: a[0] a[1] a[2] a[3] a[4] a[5]
	 //-----------------------------------------------------------------------------


	 /**
     *
     */
    public void insertionSortByDirector ()
	  	 {
			 FILE key = new FILE();

	  	    // Outside loop starts from object[1] and goes to object[count-1]
	  	    for (int index = 1; index < count; index++)
	  	    {
	  	       // initialize key as the number in the current outside loop position
	  	       key = collection[index];

	  	       // initialize position as the current outside loop position
	  	       int position = index;

	  	       // Inside loop moves smaller objects left and larger ones right
	  	       while (position > 0 && key.getDirector().compareTo(collection[position-1].getDirector()) < 0)
	  	          {
	  	             // replace smaller number on right by larger number on its left
	  	             collection[position] = collection[position-1];

	  	             // move back one position
	  	             position--;
	  	          }
	  	          // after inside loop is complete, place key where it belongs in sequence
	  	          collection[position] = key;
	  	       }
         }


   //-----------------------------------------------------------------
     //  Use a binary search to find a specific CD
     //-----------------------------------------------------------------

     /**
     *
     * @param targetTitle
     * @return
     */
    public FILE binarySearch(String targetTitle)
     {
         int min=0;                          // lowest position for search range
         int max=count;                      // highest position for search range
         int mid=0;                          // middle position for search range
         boolean found = false;              // boolean variable tells if title found

         //  loop looks for a match or min > max
         while (!found && min <= max)
         {
             // calculate middle position in the range
             mid = (min+max)/2;
             // compare the title entered to the title of the mid position CD
             if(collection[mid].getTitle().compareTo(targetTitle) == 0)
                 found = true;               // we have a match - found is true
             else if (collection[mid].getTitle().compareTo(targetTitle) > 0)
                 max = mid-1;                // too high, use max 1 lower than mid
             else
                 min = mid+1;                // too low, use min 1 higher than mid
         }

         // determine if there was a match
         if (found) return collection[mid];  // if so, return the FILE that matches
         else return null;                   // if not, return an empty FILE object
    }//end binary search

   //-----------------------------------------------------------------
   //  Writes FILE collection to disk file
   //  Overlay any existing data
   //  Create a new file if one does not exist and then write to it
   //-----------------------------------------------------------------

//********************** Different Outputs for Different Collections *************************
    /**
     *
     */
    public void writeToFileA()
   {
       // Try to write to a file
       try
       {
          // create a file writer object called fw which will overlay any existing data
          FileWriter fw = new FileWriter("Movie Collection.txt", false);
           try (BufferedWriter bw = new BufferedWriter (fw)) {
               String s;

               for(int i=0; i<count; i++)
               {
                   // create a string s composed of fields separated by | character
                       s = "";
                   s += collection[i].getTitle() + "/";
                   s += collection[i].getDirector() + "/";
                   s += collection[i].getYear() + "/";
                   s += collection[i].getCost() + "/";
                   s += collection[i].getBluRay() + "\r\n";
                   // write the string containing one FILE object to the write buffer
                   bw.write (s);
               }

               // Transfer a partially filled buffer to the disc
               bw.flush();
           }

       }

       // If there is an file IO error, display why it occurred
       catch(IOException e)
       {
          e.printStackTrace();
       }
   }//end writeToFileA

    /**
     *
     */
    public void writeToFileB()
      {
          // Try to write to a file
          try
          {
             // create a file writer object called fw which will overlay any existing data
             FileWriter fw = new FileWriter("Music Collection.txt", false);
              try (BufferedWriter bw = new BufferedWriter (fw)) {
                  String s;

                  for(int i=0; i<count; i++)
                  {
                      // create a string s composed of fields separated by | character
                          s = "";
                      s += collection[i].getTitle() + "/";
                      s += collection[i].getDirector() + "/";
                      s += collection[i].getYear() + "/";
                      s += collection[i].getCost() + "/";
                      s += collection[i].getBluRay() + "\r\n";
                      // write the string containing one FILE object to the write buffer
                      bw.write (s);
                  }

                  // Transfer a partially filled buffer to the disc
                  bw.flush();
              }

          }

          // If there is an file IO error, display why it occurred
          catch(IOException e)
          {
             e.printStackTrace();
          }
   }//end writeToFileB

    /**
     *
     */
    public void writeToFileC()
      {
          // Try to write to a file
          try
          {
             // create a file writer object called fw which will overlay any existing data
             FileWriter fw = new FileWriter("Video Game Collection.txt", false);
              try (BufferedWriter bw = new BufferedWriter (fw)) {
                  String s;

                  for(int i=0; i<count; i++)
                  {
                      // create a string s composed of fields separated by | character
                          s = "";
                      s += collection[i].getTitle() + "/";
                      s += collection[i].getDirector() + "/";
                      s += collection[i].getYear() + "/";
                      s += collection[i].getCost() + "/";
                      s += collection[i].getBluRay() + "\r\n";
                      // write the string containing one FILE object to the write buffer
                      bw.write (s);
                  }

                  // Transfer a partially filled buffer to the disc
                  bw.flush();
              }

          }

          // If there is an file IO error, display why it occurred
          catch(IOException e)
          {
             e.printStackTrace();
          }
   }//end writeToFileC

//********************** Different Outputs for Different Collections *************************



    /**
     *
     */
    public void appendToFileA()
      {
          // Try to write to a file
          try
          {
             // create a file writer object called fw which will overlay any existing data
             FileWriter fw = new FileWriter("Movie Collection.txt", true);
              try (BufferedWriter bw = new BufferedWriter (fw)) {
                  String s;

                  for(int i=0; i<count; i++)
                  {
                      // create a string s composed of fields separated by | character
                          s = "";
                      s += collection[i].getTitle() + "/";
                      s += collection[i].getDirector() + "/";
                      s += collection[i].getYear() + "/";
                      s += collection[i].getCost() + "/";
                      s += collection[i].getBluRay() + "\r\n";
                      // write the string containing one FILE object to the write buffer
                      bw.write (s);
                  }

                  // Transfer a partially filled buffer to the disc
                  bw.flush();
              }

          }

          // If there is an file IO error, display why it occurred
          catch(IOException e)
          {
             e.printStackTrace();
          }
   }//end appendToFileA

    /**
     *
     */
    public void appendToFileB()
         {
             // Try to write to a file
             try
             {
                // create a file writer object called fw which will overlay any existing data
                FileWriter fw = new FileWriter("Music Collection.txt", true);
                 try (BufferedWriter bw = new BufferedWriter (fw)) {
                     String s;

                     for(int i=0; i<count; i++)
                     {
                         // create a string s composed of fields separated by | character
                             s = "";
                         s += collection[i].getTitle() + "/";
                         s += collection[i].getDirector() + "/";
                         s += collection[i].getYear() + "/";
                         s += collection[i].getCost() + "/";
                         s += collection[i].getBluRay() + "\r\n";
                         // write the string containing one FILE object to the write buffer
                         bw.write (s);
                     }

                     // Transfer a partially filled buffer to the disc
                     bw.flush();
                 }

             }

             // If there is an file IO error, display why it occurred
             catch(IOException e)
             {
                e.printStackTrace();
             }
   }//end appendToFileB

    /**
     *
     */
    public void appendToFileC()
         {
             // Try to write to a file
             try
             {
                // create a file writer object called fw which will overlay any existing data
                FileWriter fw = new FileWriter("Video Game Collection.txt", true);
                 try (BufferedWriter bw = new BufferedWriter (fw)) {
                     String s;

                     for(int i=0; i<count; i++)
                     {
                         // create a string s composed of fields separated by | character
                             s = "";
                         s += collection[i].getTitle() + "/";
                         s += collection[i].getDirector() + "/";
                         s += collection[i].getYear() + "/";
                         s += collection[i].getCost() + "/";
                         s += collection[i].getBluRay() + "\r\n";
                         // write the string containing one FILE object to the write buffer
                         bw.write (s);
                     }

                     // Transfer a partially filled buffer to the disc
                     bw.flush();
                 }

             }

             // If there is an file IO error, display why it occurred
             catch(IOException e)
             {
                e.printStackTrace();
             }
   }//end appendToFileC


    /**
     *
     */
    public void scannerReadFileA()
   {
       // Try to read a file
       try
       {
          Scanner fileScan, recordScan;

          // create the working data items
          String title, director, record;
          double cost;
          int year;
          boolean bluRay;
          count = 0;
          totalCost = 0.0;

          fileScan = new Scanner(new File("Movie Collection.txt"));

          // outside loop to read consecutive FILE's until all are read
          while((fileScan.hasNext()))
          {
             if (currentSize == 0)
                 currentSize = 100;
             if (count >= currentSize)
                 increaseSize();


             // each field of record is separated from the other by the / character
             record = fileScan.nextLine();
             //System.out.println("Record - "+record);
             recordScan = new Scanner(record);
             recordScan.useDelimiter("/");

             title = recordScan.next();
             //System.out.println("Title - " + title);
             director = recordScan.next();
             //System.out.println("Artist - " + director);
             year = recordScan.nextInt();
             //System.out.println("Tracks - " + year);
             cost = recordScan.nextDouble();
             //System.out.println("Value - " + cost);
             bluRay = recordScan.nextBoolean();
             //System.out.println("Tracks - " + bluRay);

             // create a FILE object composed of the tokens just read
             collection[count] = new FILE (title, director, year, cost, bluRay);
             // update the totalValue and count
             totalCost += cost;
             count++;

          }
          fileScan.close();
       }
       // If there is an file IO error, display why it occurred
       catch(IOException e)
       {
          e.printStackTrace();
       }
   }
   
    /**
     *
     */
    public void scannerReadFileB()
   {
       // Try to read a file
       try
       {
          Scanner fileScan, recordScan;

          // create the working data items
          String title, director, record;
          double cost;
          int year;
          boolean bluRay;
          count = 0;
          totalCost = 0.0;

          fileScan = new Scanner(new File("Music Collection.txt"));

          // outside loop to read consecutive FILE's until all are read
          while((fileScan.hasNext()))
          {
             if (currentSize == 0)
                 currentSize = 100;
             if (count >= currentSize)
                 increaseSize();


             // each field of record is separated from the other by the / character
             record = fileScan.nextLine();
             //System.out.println("Record - "+record);
             recordScan = new Scanner(record);
             recordScan.useDelimiter("/");

             title = recordScan.next();
             //System.out.println("Title - " + title);
             director = recordScan.next();
             //System.out.println("Artist - " + director);
             year = recordScan.nextInt();
             //System.out.println("Tracks - " + year);
             cost = recordScan.nextDouble();
             //System.out.println("Value - " + cost);
             bluRay = recordScan.nextBoolean();
             //System.out.println("Tracks - " + bluRay);

             // create a FILE object composed of the tokens just read
             collection[count] = new FILE (title, director, year, cost, bluRay);
             // update the totalValue and count
             totalCost += cost;
             count++;

          }
          fileScan.close();
       }
       // If there is an file IO error, display why it occurred
       catch(IOException e)
       {
          e.printStackTrace();
       }
   }
    
     /**
     *
     */
    public void scannerReadFileC()
   {
       // Try to read a file
       try
       {
          Scanner fileScan, recordScan;

          // create the working data items
          String title, director, record;
          double cost;
          int year;
          boolean bluRay;
          count = 0;
          totalCost = 0.0;

          fileScan = new Scanner(new File("Video Game Collection.txt"));

          // outside loop to read consecutive FILE's until all are read
          while((fileScan.hasNext()))
          {
             if (currentSize == 0)
                 currentSize = 100;
             if (count >= currentSize)
                 increaseSize();


             // each field of record is separated from the other by the / character
             record = fileScan.nextLine();
             //System.out.println("Record - "+record);
             recordScan = new Scanner(record);
             recordScan.useDelimiter("/");

             title = recordScan.next();
             //System.out.println("Title - " + title);
             director = recordScan.next();
             //System.out.println("Artist - " + director);
             year = recordScan.nextInt();
             //System.out.println("Tracks - " + year);
             cost = recordScan.nextDouble();
             //System.out.println("Value - " + cost);
             bluRay = recordScan.nextBoolean();
             //System.out.println("Tracks - " + bluRay);

             // create a FILE object composed of the tokens just read
             collection[count] = new FILE (title, director, year, cost, bluRay);
             // update the totalValue and count
             totalCost += cost;
             count++;

          }
          fileScan.close();
       }
       // If there is an file IO error, display why it occurred
       catch(IOException e)
       {
          e.printStackTrace();
       }
   }

//********************** Different Outputs for Different Collections **********************************************



   //-----------------------------------------------------------------
   //  Returns a report describing the FILE collection.
   //-----------------------------------------------------------------
   @Override
   public String toString()
   {
      NumberFormat fmt = NumberFormat.getCurrencyInstance();

      String report = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
      report += "My Collection\n\n";

      report += "Number of entries : " + count + "\n";
      report += "Total cost: " + fmt.format(totalCost) + "\n";
      report += "Average cost: " + fmt.format(totalCost/count);

      report += "\n\nEntry List:\n\n";

      for (int file = 0; file < count; file++)
         report += collection[file].toString() + "\n";

      return report;
   }

   //-----------------------------------------------------------------
   //  Increases the capacity of the collection by creating a
   //  larger array and copying the existing collection into it.
   //-----------------------------------------------------------------
   private void increaseSize ()
   {
      FILE[] temp = new FILE[collection.length * 2];

      for (int file = 0; file < collection.length; file++)
         temp[file] = collection[file];

      collection = temp;
   }
}
