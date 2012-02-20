// Javed Ahamed Lecture #2

import java.io.*;
import java.*;
import java.util.*;
import java.util.Scanner;  //for input
import java.util.Arrays;


public class CMSC351P1lib {

	private int comps;
	private int rands; //what was this supposed to be used for?
	public void resetComps() {comps=0;}
	public int getComps() {return comps;}


/* When I first started thinking about this, I just tried random swaps in the 
 * list to see if i could find any patterns and while sometimes i would get 
 * close there would always be some case that the idea didn't work for. 
 * Eventually I just tried to sort the list, even though sorting's most efficient
 * runtime is nlogn, I thought since we know the list size, we might use that to
 * our advantage. I started with the outlier case of 5-4-3-2-1 and tried to sort 
 * it to 1-2-3-4-5, because the middle element would then be the median. The way
 * I did it index 0 would always be less than 1 and 3, and 3 would be less than 4.
 * Eventually, for different cases new comparisons needed to be added, but the 
 * basic idea of "sorting" the list from index 0 to 4 and then just returning the 
 * "third" element is what i built it on. Another way to explain it is you take 
 * out four of the indexes, by putting restrictions 0<1&3 and 3<4, and after that 
 * the comps. are for trying to find out where in that list index 2 fits, at which
 * point you will know the median. 
 */
	public int Med5 (int[] ListOf5) {

		comps += 1;
		if(ListOf5[0] > ListOf5[1]){
			//I decided to use XOR switch to avoid using a third variable.
			ListOf5[0] = ListOf5[0]^ListOf5[1];
			ListOf5[1] = ListOf5[0]^ListOf5[1];
			ListOf5[0] = ListOf5[0]^ListOf5[1];
		}

		comps += 1;
		if(ListOf5[3] > ListOf5[4]){
			ListOf5[3] = ListOf5[3]^ListOf5[4];
			ListOf5[4] = ListOf5[3]^ListOf5[4];
			ListOf5[3] = ListOf5[3]^ListOf5[4];
		}

		comps += 1;
		if(ListOf5[0] > ListOf5[3]){
			ListOf5[0] = ListOf5[0]^ListOf5[3];
			ListOf5[3] = ListOf5[0]^ListOf5[3];
			ListOf5[0] = ListOf5[0]^ListOf5[3];

			ListOf5[1] = ListOf5[1]^ListOf5[4];
			ListOf5[4] = ListOf5[1]^ListOf5[4];
			ListOf5[1] = ListOf5[1]^ListOf5[4];			
		}

		//The 3 comps to "sort" the list end here ^^
		
		comps += 1;
		if(ListOf5[2] > ListOf5[1]){ 

			comps += 1;
			if(ListOf5[3] > ListOf5[1]){
				comps += 1;
				if(ListOf5[3] > ListOf5[2]){
					return ListOf5[2];
				}else{
					return ListOf5[3];
				}
			}else{
				comps += 1;
				if(ListOf5[4] > ListOf5[1]){
					return ListOf5[1];
				}else{
					return ListOf5[4];
				}
			}
		}else{ //ListOf5[1] > ListOf5[2]
			
			comps += 1;
			if(ListOf5[2] > ListOf5[3]){
				comps += 1;
				if(ListOf5[2] > ListOf5[4]){
					return ListOf5[4];
				}else{
					return ListOf5[2];
				}
			}else{
				comps += 1;
				if(ListOf5[1] > ListOf5[3]){
					return ListOf5[3];
				}else{
					return ListOf5[1];
				}
			}
		}
	}
}


