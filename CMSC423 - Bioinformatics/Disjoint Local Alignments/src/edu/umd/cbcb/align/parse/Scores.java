package edu.umd.cbcb.align.parse;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;

import edu.umd.cbcb.align.Util;


/**
 * Scores for matching two characters
 * 
 * @author lynxoid
 *
 */
public class Scores {

	/**
	 * Map of characters to maps of characters to their costs
	 */
	private Map<Character,Map<Character,Float>> costs = new HashMap<Character, Map<Character, Float>>();

	/**
	 * gap opening score
	 */
	private float gapOpeningCost = 0;

	public Scores() {
	}

	public void addScore(char char1, char char2, float score) {
		if (!costs.containsKey(char1) ) 
			costs.put(char1, new HashMap<Character, Float>());
		costs.get(char1).put(char2, score);
	}

	public float getScore(char char1, char char2) throws ScoreParsingException {
		if (costs.containsKey(char1) ) {
			if (costs.get(char1).containsKey(char2))
				return costs.get(char1).get(char2);
		}
		if (costs.containsKey(char2) ) {
			if (costs.get(char2).containsKey(char1))
				return costs.get(char2).get(char1);
		}
		throw new ScoreParsingException(Util.NO_SUCH_PAIR + ": " + char1 + " " + char2);
	}
	
	public float getGapOpeningCost() {
		return this.gapOpeningCost;
	}
	public void setGapOpeningCost(float f) {
		this.gapOpeningCost = f;
	}

	/**
	 * Parse scores file
	 * @param path
	 * @return
	 */
	public static Scores parseScores(String path) throws ScoreParsingException {
		System.out.println("Parsing scores: " + path);
		try {
			FileInputStream fis = new FileInputStream(path);
			Scores scores = new Scores();
			
			BufferedReader in = new BufferedReader(new InputStreamReader(fis));
			String line;
			
			while ( (line = in.readLine()) != null) {
				String [] parts = line.split(" ");
				if (parts.length == 3) {
					if (parts[0].equals("-") && parts[1].equals("-")) {
						scores.gapOpeningCost = Float.parseFloat(parts[2]);
					}
					else {
						// check if both are single characters
						if (parts[0].length() > 1 || parts[1].length() > 1)
							throw new ScoreParsingException(Util.NOT_A_CHAR + ": " + parts[0] + " " + parts[1]);
						
						// check that both are characters
						if (!parts[0].matches("[-a-zA-Z]") || !parts[1].matches("[-a-zA-Z]"))
							throw new ScoreParsingException(Util.NOT_A_CHAR + ": " + parts[0] + " " + parts[1]);
						
						// if already contains the reverse
						if (scores.contains(parts[1], parts[0]))
							throw new ScoreParsingException(Util.DUPLICATE + ": " + parts[0] + " " + parts[1]);
						// otherwise add the pair
						scores.addScore(parts[0].charAt(0),  parts[1].charAt(0), Float.parseFloat(parts[2]));
					}
						
				}
				else {
					throw new ScoreParsingException(Util.TOO_FEW_ARGS + ": " + line);
				}
			}
			System.out.println("Parsed scores successfully!");
			return scores;
			
		} catch (FileNotFoundException e) {
			System.out.println("error: No such file");
		}
		catch (IOException ioe) {
			System.out.println("error: Exception reading the file " + path);
		}
		return null;
	}

	/**
	 * Returns true if there is a score for ch1, ch2 already
	 * @param ch1
	 * @param ch2
	 * @return
	 */
	private boolean contains(String ch1, String ch2) {
		if (this.costs.containsKey(ch1) && costs.get(ch1).containsKey(ch2))
			return true;
		return false;
	}

	public int getPairCount() {
		int c = 0;
		for (Map<Character, Float> m : costs.values()) {
			c += m.size();
		}
		return c;
	}	

	
}
