/*
CMSC423 Disjoint Local Alignment
Author: Javed Ahamed
*/

package edu.umd.cbcb.align;

import java.util.*;

import edu.umd.cbcb.align.alg.DisjointLocalAlignment;
import edu.umd.cbcb.align.alg.Sequence;
import edu.umd.cbcb.align.parse.FASTAParser;
import edu.umd.cbcb.align.parse.Scores;
import edu.umd.cbcb.align.parse.ScoreParsingException;
import edu.umd.cbcb.align.parse.SeqParsingException;

public class Main {

	/*
	 * Parses score.matrix, in.fasta and outputs the k best local-disjoint alignments into out.fasta
	 */
	public static void main(String[] argv) {
		if (argv.length != 4) {
			System.out.println("incorrect #args - score.matrix, in.fasta, out.fasta, k");
		} else {
			try {
				Scores scores = Scores.parseScores(argv[0]);
				Map<String, Sequence> map = FASTAParser.parseFASTA(argv[1]);
				ArrayList<Sequence> seqs = new ArrayList<Sequence>(map.values());
				if (seqs.size() != 2){
					throw new SeqParsingException("only two sequences allowed");
				}
				DisjointLocalAlignment dla = new DisjointLocalAlignment();
				//run disjoint local alignment algorithm with seqs, scores, output file path, #alignments to do
				dla.alignDLA(seqs, scores, argv[2], Integer.parseInt(argv[3]));
			} catch (ScoreParsingException e) {
				e.printStackTrace();
			} catch (SeqParsingException e) {
				e.printStackTrace();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}
}
