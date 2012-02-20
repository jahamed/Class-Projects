package foodManagement;

import GUI.View;

/** 
 * Run the main method in this class to try out the Graphical User Interface
 * 
 * @author Fawzi Emad, (C)2007
 */
public class GUIDriver {

	/** Starts up the GUI */
	public static void main(String[] args) {
		
		final Restaurant restaurant = new Restaurant("Cafe 131", 10000);

		javax.swing.SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				Thread.currentThread().setPriority(Thread.MAX_PRIORITY);		
				new View(restaurant);
			}
		});	
	}

}
