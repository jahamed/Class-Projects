package edu.umd.cbcb.align.alg;

import java.util.*;

import edu.umd.cbcb.align.Util;
import edu.umd.cbcb.align.parse.ScoreParsingException;
import edu.umd.cbcb.align.parse.Scores;

/*
 * Local Alignment with affine gaps between two sequences.
 */

public class LocalAlignmentAlgorithm {
	
	/**
	 *  a matrix to hold intermediate alignment scores for an subalignment 
	 *  ending with a match/mismatch
	 */
	private float [][] M;		// match matrix
	/**
	 * a matrix to hold alignment scores for a subalignment ending in a gap in 
	 * sequence XZ
	 */
	private float [][] X;		// ends in a gap in X
	/**
	 * a matrix to hold alignment scores for a subalignment ending in a gap in 
	 * sequence Y
	 */
	private float [][] Y;		// ends in a gap in Y
	/**
	 * tracebacks for the matrix M
	 */
	private char [][] arrowsM;	
	/**
	 * tracebacks for the matrix X
	 */
	private char [][] arrowsX;	
	/**
	 * tracebacks for the matrix Y
	 */
	private char [][] arrowsY;	
	
	/*boolean matrices that track whether a node has been visited already in an alignment*/
	private boolean[][] visitedM;
	private boolean[][] visitedX;
	private boolean[][] visitedY;
	
	/**
	 * Initialize base cases for all matrices: M, X, Y, arrows
	 * 
	 * @param x
	 * @param y
	 * @param n
	 * @param m
	 * @param scores
	 * @throws ScoreParsingException
	 */
	private void initBaseCases(Sequence x, Sequence y, int m, int n, Scores scores) throws ScoreParsingException {
		int i;

		//set first row and col to 0
		for (i = 0; i < m; i++){
			M[i][0] = 0; 
			X[i][0] = 0;
			Y[i][0] = 0;
		}
		for (i = 0; i < n; i++){
			M[0][i] = 0;
			X[0][i] = 0;
			Y[0][i] = 0;
		}
		
		//initialize arrow matrix
		for (i = 0; i < n; i++) {
			arrowsM[0][i] = '-';	// no arrows
			arrowsX[0][i] = '-';
			arrowsY[0][i] = '-';
		}
		for (i = 0; i < m; i++) {
			arrowsM[i][0] = '-';
			arrowsX[i][0] = '-';
			arrowsY[i][0] = '-';
		}	
	}
	
	/**
	 * Given two sequences x and y, computes an optimal alignment between the 
	 * two and returns the results in an AlignedPair object (alignment+score).
	 * 
	 * @param x
	 * @param y
	 * @param scores
	 * @return AlignedPair with two sequences aligned
	 * @throws ScoreParsingException
	 */
	public List<AlignedPair> align(Sequence x, Sequence y, Scores scores, int k) throws ScoreParsingException {
		
		int m = x.size() + 1;
		int n = y.size() + 1;
		int numAlignmentsNeeded = k;
		
		List<AlignedPair> alignedPairList = new ArrayList<AlignedPair>();
		
		// init matrices
		M = new float[m][n];	// match matrix
		X = new float[m][n];	// ends in a gap in X
		Y = new float[m][n];	// ends in a gap in Y
		arrowsM = new char[m][n]; // 'M' for M[i-1][j-1], 'X' for X[i-1][j-1], 'Y' for Y[i-1][j-1]
		arrowsX = new char[m][n]; // 'M' for M[i][j-1], 'X' for X[i][j-1], 'Y' for Y[i][j-1]
		arrowsY = new char[m][n]; // 'M' for M[i-1][j], 'X' for X[i-1][j], 'Y' for Y[i-1][j]
		visitedM = new boolean[m][n]; // tracks whether nodes in each matrix have been used in an alignment yet
		visitedX = new boolean[m][n];
		visitedY = new boolean[m][n];
		
		// initialize scores, arrows
		int i, j;
		float gap_start = scores.getGapOpeningCost();
		initBaseCases(x, y, m, n, scores);
		
		// align
		for (i = 1; i < m; i++) { // start with the first row
			for (j = 1; j < n; j++) {	// go through columns
				M[i][j] = Math.min(0, scores.getScore(x.getChar(i-1), y.getChar(j-1)) + getM(i,j)); /* (mis)match */
				X[i][j] = Math.min(0, scores.getScore('-', y.getChar(j-1)) /*gap extend*/ 
							+ getX(i,j, gap_start));
				Y[i][j] = Math.min(0, scores.getScore(x.getChar(i-1), '-') /*gap extend*/
							+ getY(i,j, gap_start));
			}
		}
		
		// traceback k times to add to alignedPairList
		while(numAlignmentsNeeded != 0){
			AlignedPair pair = traceback(x, y, m-1, n-1);
			alignedPairList.add(pair);
			numAlignmentsNeeded--;
		}
		
		// free memory as soon as we're done with it
		M = null;
		X = null;
		Y = null;
		System.gc(); // suggest that JVM clears memory
		
		return alignedPairList;
	}

	/**
	 * Traceback - find out where to start by comparing M[n][m], X[n][m], 
	 * Y[n][m]
	 * 
	 * @param x
	 * @param y
	 * @param m
	 * @param n
	 * @return
	 */
	private AlignedPair traceback(Sequence x, Sequence y, int m, int n) {
		int i = m;
		int j = n;
		boolean foundZero = false; //have we tracebacked to a zero?
		AlignedPair pair = new AlignedPair();
		
		Sequence newX = new Sequence(x.getName());
		Sequence newY = new Sequence(y.getName());
		
		// find which of the three matrices to start backtracking from
		char curr_matrix = '-';
		float currMin = Float.POSITIVE_INFINITY;
		
		/*Find minimum value to start traceback from all 3 matrices, checking 
		 * and excluding nodes that we have already used in previous tracebacks.
		 */
		for (int p = n; p >= 0; p--){
			for (int r = m; r >= 0; r--){
				if (M[r][p] < currMin && !visitedM[r][p]){
					currMin = M[r][p];
					curr_matrix = 'M';
					i = r;
					j = p;
				}
				if (X[r][p] < currMin && !visitedX[r][p]){
					currMin = X[r][p];
					curr_matrix = 'X';
					i = r;
					j = p;
				}
				if (Y[r][p] < currMin && !visitedY[r][p]){
					currMin = Y[r][p];
					curr_matrix = 'Y';
					i = r;
					j = p;
				}
			}
		}
		
		// build the alignment
		// loop until we reach a zero, end case for local alignment
		while (!foundZero) {
			switch(curr_matrix) {
				case 'M':
					//if we have visited the node already, start traceback again
					if(visitedM[i][j]){
						//use fresh newX and newY
						return traceback(x, y, m, n);
					}
					//reach 0, end trace
					if(M[i][j] == 0){
						visitedM[i][j] = true;
						foundZero = true;
						break;
					}
					newX.prependForeignChar(x.getChar(i-1));
					newY.prependForeignChar(y.getChar(j-1));
					visitedM[i][j] = true;
					curr_matrix = arrowsM[i][j]; 
					i--; j--; 
					break;
				case 'X':
					//if we have visited the node already, start traceback again
					if(visitedX[i][j]){
						return traceback(x, y, m, n);
					}
					//reach 0, end trace
					if(X[i][j] == 0){
						visitedX[i][j] = true;
						foundZero = true;
						break;
					}
					newX.prependForeignChar('-');
					newY.prependForeignChar(y.getChar(j-1));
					visitedX[i][j] = true;
					curr_matrix = arrowsX[i][j]; 
					j--; 
					break;
				case 'Y':
					//if we have visited the node already, start traceback again
					if(visitedY[i][j]){
						return traceback(x, y, m, n);
					}
					//reach 0, end trace
					if(Y[i][j] == 0){
						visitedY[i][j] = true;
						foundZero = true;
						break;
					}
					newX.prependForeignChar(x.getChar(i-1));
					newY.prependForeignChar('-');
					visitedY[i][j] = true;
					curr_matrix = arrowsY[i][j]; 
					i--; 
					break;
			}
		}
		
		//new pairs that have been built in traceback
		pair.setX(newX);
		pair.setY(newY);
		return pair;
	}

	
	//Functions that represent the recurrence equations on slide
	private float getM(int i, int j) {
		int index = Util.argmin(M[i-1][j-1], X[i-1][j-1], Y[i-1][j-1]);
		switch(index) {
		case 0: arrowsM[i][j] = 'M'; return M[i-1][j-1];
		case 1: arrowsM[i][j] = 'X'; return X[i-1][j-1]; 
		case 2: arrowsM[i][j] = 'Y'; return Y[i-1][j-1];
		default: return Float.POSITIVE_INFINITY; // this line should never be called
		}
	}
	
	private float getX(int i, int j, float gap_start) {
		int index = Util.argmin(M[i][j-1], X[i][j-1], Y[i][j-1]);
		switch(index) {
		case 0: arrowsX[i][j] = 'M'; return gap_start + M[i][j-1];
		case 1: arrowsX[i][j] = 'X'; return X[i][j-1]; 
		case 2: arrowsX[i][j] = 'Y'; return gap_start + Y[i][j-1];
		default: return Float.POSITIVE_INFINITY; // this line should never be called
		}
	}
	
	private float getY(int i, int j, float gap_start) {
		int index = Util.argmin(M[i-1][j], X[i-1][j], Y[i-1][j]);
		switch(index) {
		case 0: arrowsY[i][j] = 'M'; return gap_start + M[i-1][j];
		case 1: arrowsY[i][j] = 'X'; return gap_start + X[i-1][j]; 
		case 2: arrowsY[i][j] = 'Y'; return Y[i-1][j];
		default: return Float.POSITIVE_INFINITY; // this line should never be called
		}
	}
}