/************************************************************
 *                                                          *
 *  CSCI 470/680          Assignment 6         Summer 2018  *
 *                                                          *
 *  Programmer: Michele Fattoruso - Z1840898                *
 *                                                          *
 *  Date Due:   Tuesday, August 7, 2018 11:59 PM            *
 *                                                          *
 *  Purpose:    Java Concurrency and Animation              *
 *                                                          *
 ***********************************************************/

import java.awt.Dimension;

import javax.swing.JFrame;
import javax.swing.JSplitPane;

/***********************************************************
 * Main frame for the sorter application
 * 
 * @author Michele Fattoruso
 *
 */

public class SortFrame extends JFrame{

	//Variable used to serialize the object
	private static final long serialVersionUID = 1L;

	//Main method
	public static void main(String[] args) {
		
		//Running the frame on an event dispatch thread
		java.awt.EventQueue.invokeLater(new Runnable() {
			public void run() {
				//we make the interface visible, so that the user can interact with
				new SortFrame().setVisible(true);
			}
		});

	}
	
	//Constructor for the JFrame
	public SortFrame() {
		setTitle("Sorter");
		//We define the size of the frame
		setPreferredSize(new Dimension (1500,700));
		//and the action to execute on close
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		//making the JFrame not resizable
		setResizable(false);;
		//We load the components inside the frame
		loadComponents();
		//and then we pack everything, so that it gets properly displayed
		pack();
	}
	
	//Method used to load the components inside the jframe
	private void loadComponents() {
		//Initializing the JSplitPane
		JSplitPane mainPanel = new JSplitPane();
		//Setting the resizeWeight to 0.5, so that both left and right part gets the same size
		mainPanel.setResizeWeight(0.5);
		//setting setenabled to false so that the JSplitPane can't be resized
		mainPanel.setEnabled(false);
		
		//Initializing two SortPanel objects
		SortPanel leftPanel = new SortPanel();
		SortPanel rightPanel = new SortPanel();
		
		//Adding the SortPanels as left and right component of the JSpitPane
		mainPanel.setLeftComponent(leftPanel);
		mainPanel.setRightComponent(rightPanel);
	
		//adding the JSplitPane to the JFrame
		add(mainPanel);
	}

}
