package edu.umd.cbcb.align.parse;

import edu.umd.cbcb.align.Util;

/**
 * Exception class - thrown when there are errors in the scores file
 * 
 * @author lynxoid
 *
 */
public class ScoreParsingException extends Exception {
	
	private static final long serialVersionUID = 1L;
	
	private String msg;

	public ScoreParsingException(String string) {
		msg = string;
	}
	
	public String toString() {
		return Util.BAD_SCORE_MATRIX + " - " + msg;
	}

}
