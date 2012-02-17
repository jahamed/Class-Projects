package edu.umd.cbcb.align.parse;

import edu.umd.cbcb.align.Util;

/**
 * Exception class - thrown when there are errors in the sequence file
 * 
 * @author lynxoid
 *
 */
public class SeqParsingException extends Exception {
	
	private static final long serialVersionUID = 1L;
	
	private String msg;

	public SeqParsingException(String string) {
		msg = string;
	}
	
	public String toString() {
		return Util.BAD_FASTA + " - " + msg;
	}

}
