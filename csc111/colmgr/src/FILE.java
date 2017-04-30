

//********************************************************************
//  FILE.java       Author: Ali Morshid
//
//  Represents a FILE.
//********************************************************************

import java.text.NumberFormat;

/**
 *
 * @author Ali Morshid
 */
public class FILE
{
   private String title, director;
   private int year;
   private double cost;
   private boolean bluRay;

   //-----------------------------------------------------------------
   //  Creates a new FILE with the specified information.
   //-----------------------------------------------------------------
    /**
     *
     * @param title
     * @param director
     * @param year
     * @param cost
     * @param bluRay
     */
    public FILE (String title, String director, int year, double cost,
      boolean bluRay)
   {
      this.title = title;
      this.director = director;
      this.year = year;
      this.cost = cost;
      this.bluRay = bluRay;
   }

 //-----------------------------------------------------------------
   //  Creates a new FILE with the specified information.
   //-----------------------------------------------------------------
    /**
     *
     */
    public FILE ()
   {
      title = "";
      director = "";
      year = 0;
      cost = 0.0;
      bluRay = false;
   }


   //-----------------------------------------------------------------
   //  Returns a string description of this FILE.
   //-----------------------------------------------------------------
   @Override
   public String toString()
   {
      NumberFormat fmt = NumberFormat.getCurrencyInstance();

      String description;

      description = fmt.format(cost) + "\t" + year + "\t";
      description += title + "\t" + director;

      if (bluRay)
         description += "\t" + "Blu-Ray";

      return description;
   }

   //-----------------------------------------------------------------
   //  Returns the title of this FILE.
   //-----------------------------------------------------------------
    /**
     *
     * @return
     */
    public String getTitle()
   {

	 return title;
   }

   //-----------------------------------------------------------------
   //  Returns the title of this FILE.
   //-----------------------------------------------------------------
    /**
     *
     * @return
     */
    public String getDirector()
   {

   	 return director;
   }

   //-----------------------------------------------------------------
   //  Returns the title of this FILE.
   //-----------------------------------------------------------------
    /**
     *
     * @return
     */
    public int getYear()
   {

   	 return year;
   }

   //-----------------------------------------------------------------
   //  Returns the cost of the FILEs.
   //-----------------------------------------------------------------
    /**
     *
     * @return
     */
    public double getCost()
   {

   	 return cost;
   }

   //-----------------------------------------------------------------
   //  Returns the value of bluRay of the FILEs.
   //-----------------------------------------------------------------
    /**
     *
     * @return
     */
    public boolean getBluRay()
   {

     return bluRay;
   }



}
