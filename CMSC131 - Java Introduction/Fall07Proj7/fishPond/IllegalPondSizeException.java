package fishPond;

/**
 * Thrown when someone tries to construct a Pond that is just too small!
 * 
 * @author Fawzi Emad
 */
public class IllegalPondSizeException extends RuntimeException {
	
	/* Field required by all Serializable classes */
	private static final long serialVersionUID = 0;
	
	/** 
	 * @param rows number of rows attempted
	 * @param cols number of columns attempted
	 */
	public IllegalPondSizeException(int rows, int cols) {
		super("Illegal Pond size: " + rows + " rows by " + cols + " cols");
	}

}
