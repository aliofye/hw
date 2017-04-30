

/*******************************************************************************************************
//  ManagerGUI.java       Author: Ali Morshid
//
//  main method for ManagerGUI program
// PROGRAM LOGIC:
//ManagerGUI is the main class that uses the following helper classes and displays them inside a frame
-"Intro" class acts as an introductory tab where it displays a logo and a brief description
-"MoviesManagerGUIPanel", "MusicManagerGUIPanel", and "GamesManagerGUIPanel" are tabbed panes that contain panels which use objects from "FileCollection" class.
-"FileCollection" class uses the "FILE" class to create objects that are later used in the other classes.
-"FILE" class represents a FILE that is used in objects inside "FileCollection" class.
-"BG" is a class used to override the paintComponent to set a background image for the GUI.
/*********************************************************************************************************/

import java.awt.*;
import javax.swing.*;

/**
 *
 * @author Ali Morshid
 */
public class ManagerGUI
{
   //-----------------------------------------------------------------
   //  create the frame in the main method
   //-----------------------------------------------------------------
    /**
     *
     * @param args
     */
    public static void main (String[] args)
   {

	 try
	 {
	     UIManager.setLookAndFeel("com.sun.java.swing.plaf.nimbus.NimbusLookAndFeel");
	     UIManager.put("nimbusBase", new Color(255,100,100));
	     UIManager.put("textForeground", new Color(0,0,0));

	 }
	  catch(ClassNotFoundException | InstantiationException | IllegalAccessException | UnsupportedLookAndFeelException e){
	  }

      
      
      // create a JFrame object with "GUI Tunes Manager" at the top of the frame
         JFrame frame;
           frame = new JFrame ("ColMGR");

       //************************************************************************************
       JTabbedPane tp = new JTabbedPane();
	  tp.addTab ("Home", new Intro());
	  tp.addTab ("Movie Collection", new MoviesManagerGUIPanel());
	  tp.addTab ("Music Collection", new MusicManagerGUIPanel());
	  tp.addTab ("Video Game Collection", new GamesManagerGUIPanel());
	  tp.setBackground(Color.white);

      //************************************************************************************
       frame.setResizable(false);
      // set the default close operation fo the frame
	   frame.setDefaultCloseOperation (JFrame.EXIT_ON_CLOSE);
	  // add the panel to the frame
	   frame.getContentPane().add(tp);
	  // pack the frame
	   frame.pack();
      // set the frame to be visible
       frame.setVisible(true);
      //end application

  }//end main
}//end MoviesManagerGUI