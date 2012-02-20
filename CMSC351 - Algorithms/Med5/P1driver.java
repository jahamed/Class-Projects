import java.io.*;
import java.*;
import java.util.Scanner;  //for input
import java.util.Arrays;

import jsc.combinatorics.*;

public class P1driver {
	private static Scanner scanner = new Scanner( System.in );

	private static boolean VerifyMedian(int[] list, int n, int med) {
		int[] templist = new int[n];
		for (int i=0; i<n; i++) {
			templist[i] = list[i];
		}
		Arrays.sort(templist);
		return (templist[(int)(Math.ceil(n/2.0))-1] == med);
	}

	private static void PrintTheList(int[] list) {
		int n=list.length;
		for (int i=0; i<n; i++) {
			System.out.print(list[i]);
			if (i!=(n-1)) System.out.print(", ");
		}
		System.out.println();
	}




	public static void main(String [] args) throws Exception {
		int listOf5[] = {1, 2, 3, 4, 5};
		int med;
		boolean worked = true;
		int minComps=100;
		int maxComps=-1;
		
		CMSC351P1lib Med5object = new CMSC351P1lib();	
		Permutations PermDriver = new Permutations(5);
		
		int numPermutations = (int) PermDriver.countSelections();
		
		for(int i=0; i<numPermutations; i++){
			if(VerifyMedian(listOf5, 5, 
					Med5object.Med5(PermDriver.nextPermutation().toIntArray()))){
				
				if (Med5object.getComps() > maxComps){
					maxComps = Med5object.getComps();
					Med5object.resetComps();
				}else if (Med5object.getComps() < minComps){
					minComps = Med5object.getComps();
					Med5object.resetComps();
				}else{
					Med5object.resetComps();
				}
				
			}else{
				worked = false;
				break;
			}
		}
		

		if (worked) {
			System.out.println(
					"It worked!  Min="+minComps+" Max="+maxComps+"."
			); 
		}
		else {
			System.out.println("ERROR FOUND");
		}


	}

}
