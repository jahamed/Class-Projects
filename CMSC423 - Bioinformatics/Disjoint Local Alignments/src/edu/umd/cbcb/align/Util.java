package edu.umd.cbcb.align;


/**
 * Helper class -- contains error messages and argmin/argmax functions.
 * 
 * @author lynxoid
 *
 */
public class Util {

	/** 
	 * error messages
	 */
	public static final String NO_SUCH_PAIR = "No such pair";
	
	public static final String NOT_A_CHAR = "Not a single character";
	
	public static final String DUPLICATE = "Duplicate pairs";
	
	public static final String TOO_FEW_ARGS = "Too few arguments";
	
	public static final String BAD_FASTA = "error: bad fasta file";
	
	public static final String BAD_SCORE_MATRIX = "error: bad scoring matrix";
	
	public static final String SP_SCORE = "SP-score=";
	
	public static int argmax(float m, float x, float y) {
		if (m > x) {
			if (m > y) return 0;
		}
		else {
			if (x > y) return 1;
		}
		
		 return 2;
	}
	
	/**
	 * Given three float values, returns an index of the min value. If there are 
	 * ties, it prefers to return the 0's index first, then 1st.
	 * 
	 * @param m
	 * @param x
	 * @param y
	 * @return
	 */
	public static int argmin(float m, float x, float y) {
		if (m <= x) {
			if (m <= y) return 0;
		}
		else {
			if (x <= y) return 1;
		}
		
		 return 2;
	}

	/**
	 * Given three double values, returns an index of the min value. If there are 
	 * ties, it prefers to return the 0's index first, then 1st.
	 * 
	 * @param m
	 * @param x
	 * @param y
	 * @return
	 */
	public static int argmin(double m, double x, double y) {
		if (m <= x) {
			if (m <= y) return 0;
		}
		else {
			if (x <= y) return 1;
		}
		
		 return 2;
	}
	
}
