

//********************************************************************
// Intro.java       Author: Ali Morshid
//
//  main method for Intro program
// displays a logo and a brief discription
//********************************************************************

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

/**
 *
 * @author Ali Morshid
 */
public class Intro extends JPanel {

    //declare variables
    private JPanel intro;
    private JLabel logoContainer, dscr, cr;
    private ImageIcon logo;
    private JButton help;
    ButtonListener listen;

    /**
     *
     */
    public Intro() {
        // set the background of the panel by creating a new instance of class BG called intro
        intro = new BG();
        intro.setPreferredSize(new Dimension(800, 500));
       // new ImageIcon for the logo with a file path
        logo = new ImageIcon("img/logo.gif");
       //a JLabel to display the Image Icon
        logoContainer = new JLabel(null, logo, SwingConstants.CENTER);
        logoContainer.setPreferredSize(new Dimension(400, 200));
       //a JLabel to display a brief discription of the program
        dscr = new JLabel("<html>Collection Manager (ColMGR�) is a program designed <br> to safekeep all of your important collections in a <br> convenient manner.<br><br><br><br><br><br><br><br><br><br></html>", null, SwingConstants.CENTER);
        Font font = new Font("OCR A Extended", Font.BOLD, 18);
        dscr.setForeground(Color.white);
        dscr.setFont(font);
        //a JLabel to show the developer's name
        cr = new JLabel("<html>�2013 ALI MORSHID&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp</html>", null, SwingConstants.CENTER);
        cr.setForeground(new Color(255, 20, 60));
        cr.setFont(font);
        // a JButton that contains help for the user
        help = new JButton("<html><b>Help?</b></html>");
        help.setPreferredSize(new Dimension(70,30));
        help.setToolTipText("This button will help you :D");
        listen = new ButtonListener();
        help.addActionListener(listen);

        // adds dscr, help and cr to intro
        intro.add(logoContainer);
        intro.add(dscr);
        intro.add(cr);
        intro.add(help);
        //adds intro to the main frame
        add(intro);
    }//end method intro

    //button listener for help that display a joptionpane with some text
     private class ButtonListener implements ActionListener
   {
      @Override
      public void actionPerformed(ActionEvent event)
      {
      JOptionPane.showMessageDialog(null, "<html><b>Roll your mouse pointer over any<br> button to show a brief explanation<br> of it's functionality.</b></html>");
      }
   }
}//end class Intro
