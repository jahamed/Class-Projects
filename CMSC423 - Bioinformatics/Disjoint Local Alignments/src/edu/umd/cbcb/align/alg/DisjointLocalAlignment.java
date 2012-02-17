package edu.umd.cbcb.align.alg;

import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.List;

import edu.umd.cbcb.align.parse.Scores;

public class DisjointLocalAlignment {
	
	public void alignDLA(ArrayList<Sequence> sequences, Scores scores, String path, int k) throws Exception {
		Sequence x = sequences.get(0);
		Sequence y = sequences.get(1);
		List<AlignedPair> alignedPairList;
		
		LocalAlignmentAlgorithm laa = new LocalAlignmentAlgorithm();
		alignedPairList = laa.align(x, y, scores, k);
		
		saveToFile(path, alignedPairList);
	}
			
	private void saveToFile(String path, List<AlignedPair> alignedPairList) {
		try {
			FileOutputStream fos = new FileOutputStream(path);
			BufferedWriter out = new BufferedWriter(new OutputStreamWriter(fos));
			
			for(int i=0; i<alignedPairList.size(); i++){
				out.write(alignedPairList.get(i).toString());
				out.newLine();
				out.newLine();
			}
			
			out.close();
			fos.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
