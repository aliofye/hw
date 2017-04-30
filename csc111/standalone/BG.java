

//********************************************************************
//  BG.java       Author: Ali Morshid
//
//  Set's the background image for the whole GUI by overriding the paintComponent
//********************************************************************

import java.awt.Graphics;
import javax.swing.ImageIcon;
import javax.swing.JPanel;


/**
 *
 * @author Ali Morshid
 */
public class BG extends JPanel
{


    @Override
	protected void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		ImageIcon img;
                img = new ImageIcon("img/bg.jpg");
		g.drawImage(img.getImage(),0,0,getWidth(),getHeight(),null);

	}

}
