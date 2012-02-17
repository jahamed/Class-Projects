package edu.umd.cbcb.align.alg;

public class AlignedPair {
	
	/**
	 * a score of an optimal alignment
	 */
	private float score;
	
	/**
	 * the first sequence
	 */
	private Sequence x;
	
	/**
	 * the second sequence
	 */
	private Sequence y;
	
	public AlignedPair() {
	}

	public float getScore() {
		return score;
	}
	
	public void setScore(float value) {
		score = value;
	}

	public Sequence getX() {
		return x;
	}
	
	public void setX(Sequence newX) {
		x = newX;
	}
	
	public Sequence getY() {
		return y;
	}
	
	public void setY(Sequence value) {
		y = value;
	}
	
	public String toString() {
		return x + "\n" + y;
	}
}
