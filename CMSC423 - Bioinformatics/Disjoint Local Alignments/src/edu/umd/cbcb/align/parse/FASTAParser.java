package edu.umd.cbcb.align.parse;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;

import edu.umd.cbcb.align.alg.Sequence;

/**
 * Parse input sequences
 * 
 * @author lynxoid
 *
 */
public class FASTAParser {
	
	/**
	 * Parse the input FASTA file according to the spec. Returns a Map of 
	 * sequence names to Sequence's
	 * 
	 * @param path
	 * @return
	 * @throws SeqParsingException
	 * @throws IOException 
	 */
	public static Map<String, Sequence> parseFASTA(String path) throws SeqParsingException, IOException {
		System.out.println("Parsing sequences: " + path);
		
		FileInputStream fis = new FileInputStream(path);		
		BufferedReader in = new BufferedReader(new InputStreamReader(fis));
		String line, name = null;
		StringBuffer seq = null;
		Map<String, Sequence> sequences = new HashMap<String, Sequence>();
		
		while ( (line = in.readLine()) != null) {
			line = line.trim(); // remove whitespace in the beg. of a line, at the end of a line
			if (line.startsWith(">") ) {
				// store the previous sequence
				if (seq != null) {
					
					sequences.put(name, new Sequence(seq.toString().toCharArray(), name));
					name = null;
				}
				
				line = line.substring(1);
				String [] parts = line.split(" ");
				if (parts.length < 1)
					throw new SeqParsingException("No sequence name provided");
				name = parts[0]; // ignore the rest of the line
				
				// if no name - have a right to flip out
				if (name.length() < 1)
					throw new SeqParsingException("Requires a sequence name");
				if (sequences.containsKey(name))
					throw new SeqParsingException("Sequence name not unique " + name);
				
				seq = new StringBuffer();
			}
			else {
				// otherwise replace all whitespaces and append to a string
				if (seq == null)
					seq = new StringBuffer();
					seq.append(line.replaceAll("[ \t\n]", ""));
			}
		}
		
		in.close();
		fis.close();
		
		// add the last sequence
		if (sequences.containsKey(name))
			throw new SeqParsingException("Sequence name not unique");
		
		if (sequences != null && seq  != null && name != null) {
			sequences.put(name, new Sequence(seq.toString().toCharArray(), name));
			System.out.println("Parsed sequences successfully: " + sequences.size());
		}
		
		return sequences;
	}
}
