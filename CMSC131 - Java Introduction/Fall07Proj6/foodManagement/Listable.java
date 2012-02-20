package foodManagement;

/**
 * Objects that implement this interface (and are immutable)can be put into a 
 * SortedListOfImmutables.
 */
public interface Listable {
	/**
	 * Getter for the name of the item
	 * @return name of the item
	 */
	public String getName();
	
	/**
	 * Getter for the wholesale cost of the item
	 * @return wholesale cost of the item
	 */
	public int getWholesaleCost();
	
	/**
	 * Getter for the retail cost of the item
	 * @return retail cost of the item
	 */
	public int getRetailValue();
	
	public String toString();
}
