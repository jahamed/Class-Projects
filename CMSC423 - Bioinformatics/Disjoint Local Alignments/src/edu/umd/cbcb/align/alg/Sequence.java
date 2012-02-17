package edu.umd.cbcb.align.alg;

import java.util.ArrayList;

public class Sequence {
	
	/**
	 * Sequence characters
	 */
	private ArrayList<Character> characters = new ArrayList<Character>();
	
	/**
	 * Sequence name
	 */
	private String name;
	
	/**
	 * Default constructor
	 * 
	 * @param chs - sequence characters
	 * @param name - sequence name
	 */
	public Sequence(char [] chs, String name) {
		int i, len = chs.length;
		for (i = 0; i < len; i++) {
			characters.add(chs[i]);
		}
		this.name = name;
	}
	
	/**
	 * Create an empty sequence with a given name
	 * @param name
	 */
	public Sequence(String name){
		this.name = name;
	}
	
	// insert a "foreign" character into a sequence
	public void prependForeignChar(char c) {
		characters.add(0, c);
	}
	
	// insert a "foreign" character into a sequence
	public void insertForeignChar(char c, int index) {
		characters.add(index, c);
	}
	
	public char getChar(int i) {
		return characters.get(i);
	}
	
	
	/**
	 * returns the number of characters in the original sequence
	 * @return
	 */
	public int size() {
		return characters.size();
	}
	
	/**
	 * FASTA sequence name
	 * @return
	 */
	public String getName() {
		return name;
	}
	
	public String toString() {
		String str = ">" + name + "\n";
		for (char c : characters) {
			str += String.valueOf(c);
		}
		return str;
	}
}
