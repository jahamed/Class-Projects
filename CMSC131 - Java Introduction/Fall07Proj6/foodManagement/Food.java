package foodManagement;


import java.awt.MediaTracker;
import java.awt.Panel;
import java.awt.Toolkit;
import java.awt.Image;

/*
 * STUDENTS:  DO NOT MODIFY THIS CLASS! 
 */

/** 
 * An IMMUTABLE class that represents an item that might be part of an entree
 * in a restaurant.  (For example, Toast or Coffee.)
 * 
 * A food object has a name (String), a wholesale cost measured in pennies (int),
 * a retail price measured in pennies (int), and a small picture that depicts
 * the item (java.awt.Image). <br><br>
 * 
 * Note that the constructor is private, so the only available Food objects
 * are those that are found in the public static array of Food objects called
 * FOOD_OBJECTS.  (You cannot use "new" to instantiate a Food object, you must
 * use the ones that are already in the FOOD_OBJECTS array.)
 */
public class Food implements Listable {

	private String name;
	private int wholesaleCost;
	private int retailCost;
	private Image image;
	
	/**
	 * This array is populated with Food items that are available for use.
	 * 
	 * Use this array any time you need a Food object.  The constructor for
	 * the Food class is private, so the elements of this array are the only
	 * Food objects available.  (You cannot create new ones.)
	 */
	public static final Food[] FOOD_OBJECTS = 
	{ new Food("Bacon", 89, 185, "Bacon.jpg"), 
		new Food("Waffle", 178, 350, "Waffle.jpg"),
		new Food("Egg", 47, 89, "Egg.jpg"),
		new Food("Orange Juice", 77, 199, "OrangeJuice.jpg"),
		new Food("Milk", 52, 179, "Milk.jpg"),
		new Food("Toast", 66, 125, "Toast.jpg"),
		new Food("Hashbrowns", 127, 195, "Hashbrowns.jpg"),
		new Food("Pancakes", 179, 350, "Pancakes.jpg"),
		new Food("Coffee", 67, 125, "Coffee.jpg"),
		new Food("Cereal", 129, 275, "Cereal.jpg"),
		new Food("Donut", 89, 129, "Donut.jpg"),
		new Food("Melon", 98, 159, "Melon.jpg"),
		new Food("Pie", 195, 275, "Pie.jpg"),
		new Food("Croissant", 106, 125, "Croissant.jpg")
	};

	private Food(String name, int wholesaleCost, int retailCost, String imageName) {
		this.name = name;
		this.wholesaleCost = wholesaleCost;
		this.retailCost = retailCost;
		this.image = Toolkit.getDefaultToolkit().getImage(imageName);
		
		/*  Java normally loads images in a background thread.
		 *  This waits for the image to finish loading before moving on with
		 *  the rest of the program.  That helps to keep things
		 *  synchronized properly.
		 */
		try {
			MediaTracker tracker = new MediaTracker(new Panel());
			tracker.addImage(image, 0);
			tracker.waitForID(0);
			if (tracker.statusID(0,true) != MediaTracker.COMPLETE) { 
				throw new RuntimeException("Unable to load " + imageName);
			}
		} catch(InterruptedException e) {
			// won't be interrupted, so no worries :-)
		}
	}

	/**
	 * Getter for the Image associated with this food.  (It's a very small
	 * picture of the food item.)
	 * 
	 * @return a picture representing this item
	 */
	public Image getImage() {
		return image;  // technically, this is a privacy leak!  :-)
	}

	/**
	 * Getter for the name of this food.
	 * 
	 * @return the name of this food
	 */
	public String getName() {
		return name;
	}

	/**
	 * Getter for the wholesale cost of this food, measured in pennies.
	 * 
	 * @return wholesale cost for this food item in pennies.
	 */
	public int getWholesaleCost() {
		return wholesaleCost;
	}

	/**
	 * Getter for the retail cost of this food, measured in pennies.
	 * 
	 * @return retail cost for this food item in pennies.
	 */
	public int getRetailValue() {
		return retailCost;
	}

	/**
	 * Checks if the current object is equal to the parameter.  Note:
	 * only the NAMES of the foods are compared.  If the two foods have
	 * the same name, they are considered equal!
	 * 
	 * @param other Food item to be compared with the current object
	 * @return true if the two Foods have the same name, false otherwise
	 */
	public boolean equals(Food other) {
		return (name.equals(other.name));
	}

	/**
	 * Returns the name of the food.
	 * 
	 * @return the name of the food
	 */
	public String toString() {
		return name;
	}
}
