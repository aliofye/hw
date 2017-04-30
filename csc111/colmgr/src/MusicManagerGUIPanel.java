

//********************************************************************
//  MusicManagerGUIPanel.java       Author: Ali Morshid
//
//  Uses a GUI interface to manage a file of FILE's
//********************************************************************

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.Scanner;
import java.io.*;


/**
 *
 * @author Ali Morshid
 */
public class MusicManagerGUIPanel extends JPanel
{

   // declare data types for title, artist, value and tracks
   private String title, director;
   private int year;
   private double cost;
   private boolean bluRay;

   // create a Scanner object called scan for keyboard input
   static Scanner scan = new Scanner(System.in);

   // create radio buttons, labels, text areas, scroll panes
   // listeners, groups and panels
   JButton readB, addB, deleteB, updateB, sortTitleB,sortDirectorB;
   JButton displayB, findB, writeB, appendB, browseB;
   JLabel headingL;
   JTextArea ta;
   JScrollPane sp;
   ButtonListener listen;
   ButtonGroup group;
   JPanel panel, centerPanel, eastPanel, westPanel, northPanel, southPanel;


   // create a FileCollection object called music
   FileCollection music;

    /**
     *
     */
    public MusicManagerGUIPanel()
   {
      // create the array of FILE objects
      music = new FileCollection();
      // create the radio button group
      group = new ButtonGroup();

      // create the text area and scrolling pane
      ta = new JTextArea("Music Listings", 35, 60);
      ta.setBackground (new Color(255,20,60));
      ta.setForeground (Color.white);
      Font fontB = new Font("OCR A Extended", Font.BOLD, 16);
      ta.setFont (fontB);
      sp = new JScrollPane(ta);

      // create the page heading in special font
      //String heading = JOptionPane.showInputDialog("Enter title for management system:");
      headingL = new JLabel("Music");//"FILE File Management System"
      int style = Font.BOLD;//Font.BOLD + Font.ITALIC;
      headingL.setFont (new Font ("OCR A Extended", style ,36));
      headingL.setForeground(Color.white);

      // create main panel, color, layout and dimensions
      panel = new BG();
      panel.setBackground (Color.yellow);
      panel.setPreferredSize(new Dimension (800, 500));
      panel.setLayout(new BorderLayout());

      // create the north panel with color and headingL
      northPanel = new BG();
      northPanel.setBackground(Color.blue);
      northPanel.add(headingL);

      // create the south panel with color
      southPanel = new BG();
      southPanel.setBackground(Color.blue);

      // create the center panel, color and JScrollPane(ta)
      centerPanel = new BG();
      centerPanel.setBackground(Color.blue);
      centerPanel.add(sp);

      // create the east panel with color
      eastPanel = new BG();
      eastPanel.setBackground (Color.blue);

      // create the west panel with color and grid layout of 11 rows and 1 column
      westPanel = new BG();
      westPanel.setBackground (Color.blue);
      westPanel.setLayout(new GridLayout(11,1));

      // create the radio button group listener
      listen = new ButtonListener();

      // create all the radio buttons, including listener, color and group
      readB = new JButton ("Read File");
      readB.addActionListener(listen);
      readB.setToolTipText("Reads collection from file.");
      group.add(readB);

      addB = new JButton ("Add Music");
      addB.addActionListener(listen);
      addB.setToolTipText("Adds a new Song.");
      group.add(addB);

      deleteB = new JButton ("Delete Music");
      deleteB.addActionListener(listen);
      deleteB.setToolTipText("Deletes an old Song.");
      group.add(deleteB);

      updateB = new JButton ("Update Music");
      updateB.addActionListener(listen);
      updateB.setToolTipText("Updates an old Song.");
      group.add(updateB);

      sortTitleB = new JButton ("Sort By Title");
      sortTitleB.addActionListener(listen);
      sortTitleB.setToolTipText("Sorts collection by Title.");
      group.add(sortTitleB);

      sortDirectorB = new JButton ("Sort By Artist");
      sortDirectorB.addActionListener(listen);
      sortDirectorB.setToolTipText("Sorts collection by Artist.");
      group.add(sortDirectorB);

      displayB = new JButton ("Display All");
      displayB.addActionListener(listen);
      displayB.setToolTipText("Display all entries in the collection.");
      group.add(displayB);

      findB = new JButton ("Find Music");
      findB.addActionListener(listen);
      findB.setToolTipText("Find a specific entry in the collection.");
      group.add(findB);

      writeB = new JButton ("Save");
      writeB.addActionListener(listen);
      writeB.setToolTipText("Saves collection to a file.");
      group.add(writeB);

      appendB = new JButton ("Append");
      appendB.addActionListener(listen);
      appendB.setToolTipText("Appends collection to a file.");
      group.add(appendB);

      browseB = new JButton ("Browse");
      browseB.addActionListener(listen);
      browseB.setToolTipText("Browse for a file.");
      group.add(browseB);

      // place radio button group in west panel
      westPanel.add(readB);
      westPanel.add(addB);
      westPanel.add(deleteB);
      westPanel.add(updateB);
      westPanel.add(sortTitleB);
      westPanel.add(sortDirectorB);
      westPanel.add(displayB);
      westPanel.add(findB);
      westPanel.add(writeB);
      westPanel.add(appendB);
      westPanel.add(browseB);

      // place all panels in the Border Layout positions
      panel.add(northPanel, BorderLayout.NORTH);
      panel.add(southPanel, BorderLayout.SOUTH);
      panel.add(centerPanel, BorderLayout.CENTER);
      panel.add(westPanel, BorderLayout.WEST);
      panel.add(eastPanel, BorderLayout.EAST);

      // add the main panel
      add (panel);


   }

   private class ButtonListener implements ActionListener
   {
      @Override
      public void actionPerformed(ActionEvent event)
      {
          // check for which radio button was clicked

          // is event readB
          if (event.getSource() == readB)
          {
                // read file
                music.scannerReadFileB();
                JOptionPane.showMessageDialog(null, "File Read Successfully");
                ta.setText(music.toString());
          }

          // else is event addB
          else if (event.getSource() == addB)
          {
                // enter information about the CD
                enterFILE();
                // add a CD
                music.addFILE(title, director, year, cost, bluRay);
                JOptionPane.showMessageDialog(null, "File Added Successfully");
                ta.setText(music.toString());
          }

          // else is event deleteB
          else if (event.getSource() == deleteB)
          {
                // delete a CD using a dialog box to get title
                title = JOptionPane.showInputDialog("Title: ");
                music.subFILE(title);
                JOptionPane.showMessageDialog(null, "File Deleted Successfully");
                ta.setText(music.toString());
          }

          // else is event updateB
          else if (event.getSource() == updateB)
          {
                // enter the proper information for the CD
	            enterFILE();
	            // update a CD
                music.updFILE (title, director, year, cost, bluRay);
                JOptionPane.showMessageDialog(null, "File Updated Successfully");
                ta.setText(music.toString());
          }

          // else is event sortTitleB
          else if (event.getSource() == sortTitleB)
          {
                // sort by title using the selectionSort method
                music.selectionSortByTitle();
                ta.setText(music.toString());
          }

          // else is event sortArtistB
          else if (event.getSource() == sortDirectorB)
          {
                // sort by artist using the insertionSort method
	            music.insertionSortByDirector();
	            ta.setText(music.toString());
          }

          // else is event findB
          else if (event.getSource() == findB)
          {
                // Find a CD using a dialog box to get title
                title = JOptionPane.showInputDialog("Title: ");
                // Make sure the music object array is sorted by title
                music.selectionSortByTitle();
                FILE found = music.binarySearch (title);
                if (found == null)
                    ta.setText(title +" was not found");
                else
                    ta.setText(found.toString());
          }

          // else is event displayB
          else if (event.getSource() == displayB)
          {
                // display music collection
	            ta.setText(music.toString());
          }

          // else is event writeB
          else if (event.getSource() == writeB)
          {
                // Write to file
                music.writeToFileB();
                JOptionPane.showMessageDialog(null, "Wrote to File Successfully");
          }

          // else is event appendB
          else if (event.getSource() == appendB)
          {

	            // Append to file
                music.appendToFileB();
                JOptionPane.showMessageDialog(null, "Appended to File Successfully");
                ta.setText(music.toString());
          }

          // else is event borwseB
          else if (event.getSource() == browseB)
          {

	            // Look for a file
                browser();
          }

      }
   }

    /**
     *
     */
    public void enterFILE()
   {
      // use dialog boxes to get title, artist, value and tracks
      title =  JOptionPane.showInputDialog("Title: ");
      director = JOptionPane.showInputDialog("Artist: ");
      year = Integer.parseInt(JOptionPane.showInputDialog("Year: "));
      cost =  Double.parseDouble(JOptionPane.showInputDialog("Cost: "));
      bluRay = false;//Boolean.parseBoolean(JOptionPane.showInputDialog("BluRay Availability: "));

   }

    /**
     *
     */
    @SuppressWarnings("resource")
public void browser()
   {
      // JFileChooser brings up a dialog box which allows browsing to find a file
      JFileChooser chooser = new JFileChooser();

      int status = chooser.showOpenDialog (null);

      try
      {
          // check for no file chosen, such as pressing cancel button
          if (status != JFileChooser.APPROVE_OPTION)
             ta.setText ("No File Chosen");  // display "No File Chosen" message
          else
          {
             // 'file' will be the name of the file selected
             File file = chooser.getSelectedFile();

             // scam will be the Scanner object which reads the file
             Scanner scanA = new Scanner (file);

             // create a string which will house the contents of the file
             String info = "";

             while (scanA.hasNext())
                info += scanA.nextLine() + "\n";

             // display the contents of the file
             ta.setText (info);
          }
       }

       // If there is an file IO error, display why it occurred
       catch(IOException e)
       {
          e.printStackTrace();
       }
   }

}

