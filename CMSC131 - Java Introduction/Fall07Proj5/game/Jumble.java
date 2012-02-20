/*
 * Author: Javed Ahamed
 * CMSC131
 * 
 * This class is the implementation of a game called "Jumble." This class generates
 * puzzles by choosing a random word from the dictionary.txt file and then applies
 * different transformations to the word (swap, insert, multiple swap). The 
 * scrambled word is then displayed and the user attempts to unscramble the word 
 * using as many transformations as he or she needs.
 */

package game;
import puzzleLib.*;


public class Jumble implements Puzzle {

	private char[] originalWord, currentWord;
	private int numberOfTransformationsDone=0, numberOfAttempts=0;
	
	/*Initializes current puzzle so that it represents the sequence of 
	 *characters contained in the parameter
	 */
	public void generatePuzzle(String wordToUse){
		originalWord=new char[wordToUse.length()];
		currentWord=new char[wordToUse.length()];

		for(int i=0;i<originalWord.length;i++){
			originalWord[i]=wordToUse.charAt(i);
			currentWord[i]=wordToUse.charAt(i);
		}
	}

	//Initializes current puzzle based on a random word selected from the dictionary
	public void generateRandomScrambledPuzzle(int numLetters, int numTransformations){
		originalWord=new char[numLetters];
		currentWord=new char[numLetters];
		String wordToUse=Dictionary131.getRandomWord(numLetters);

		//Sets the originalWord and currentWord char arrays to the String wordToUse
		for(int i=0;i<numLetters;i++){
			originalWord[i]=wordToUse.charAt(i);
			currentWord[i]=wordToUse.charAt(i);
		}

		int r,firstCellSelected,secondCellSelected,transformationsLeft=numTransformations;
		numberOfTransformationsDone=numTransformations;
		while(transformationsLeft>0){
			r=Random131.getRandomInteger(3);
			firstCellSelected=Random131.getRandomInteger(wordToUse.length());
			secondCellSelected=Random131.getRandomInteger(wordToUse.length());

			if(r==0){//Swap
				swap(firstCellSelected,secondCellSelected);
				numberOfAttempts--;
			}else if(r==1){//Insert
				insert(firstCellSelected,secondCellSelected);
				numberOfAttempts--;
			}else if(r==2){//Multiple Swap
				multipleSwap(firstCellSelected,secondCellSelected);
				numberOfAttempts--;
			}
			transformationsLeft--;
		}

	}

	/*Initializes current puzzle so that it represents the sequence of
	 *characters contained in the parameter
	 */
	public void generateScrambledPuzzle(String wordToUse, int numTransformations){
		originalWord=new char[wordToUse.length()];
		currentWord=new char[wordToUse.length()];

		//Sets the originalWord and currentWord char arrays to the String wordToUse
		for(int i=0;i<originalWord.length;i++){
			originalWord[i]=wordToUse.charAt(i);
			currentWord[i]=wordToUse.charAt(i);
		}

		int r,firstCellSelected,secondCellSelected,transformationsLeft=numTransformations;
		numberOfTransformationsDone=numTransformations;
		while(transformationsLeft>0){
			r=Random131.getRandomInteger(3);
			firstCellSelected=Random131.getRandomInteger(wordToUse.length());
			secondCellSelected=Random131.getRandomInteger(wordToUse.length());

			if(r==0){//Swap
				swap(firstCellSelected,secondCellSelected);
				numberOfAttempts--;
			}else if(r==1){//Insert
				insert(firstCellSelected,secondCellSelected);
				numberOfAttempts--;
			}else if(r==2){//Multiple Swap
				multipleSwap(firstCellSelected,secondCellSelected);
				numberOfAttempts--;
			}
			transformationsLeft--;
		}

	}

	//Returns the number of user attempts at solving the puzzle
	public int getAttempts(){
		return numberOfAttempts;
	}

	/*
	 * Returns the current state of the puzzle as an array of Cell References.
	 * This includes the character in each Cell as well as the background color
	 * (yellow or white) of the cell based on the proximity of the currentWord 
	 * characters to the solution.
	 */
	public Cell[] getCurrentContentsAsCells(){
		Cell[] currentContentsAsCells=new Cell[currentWord.length];

		for(int i=0;i<currentContentsAsCells.length;i++){
			//Sets currentContentsAsCells[i] default to the Character+White Background
			currentContentsAsCells[i]=new Cell(currentWord[i], Cell.WHITE); 
			/*Checks if currentWord[i] is not at the endpoints of the array 
			and if it does not equal originalword[i]*/
			if(i>0&&i<currentWord.length-1&&currentWord[i]!=originalWord[i]){
				if(currentWord[i]==originalWord[i-1]||currentWord[i]==originalWord[i+1]){
					currentContentsAsCells[i]=new Cell(currentWord[i], Cell.YELLOW);
				}
			}else if((i==0||i==currentWord.length-1)&&currentWord[i]!=originalWord[i]){
				//Checking wrap around Left and Right
				if(i==0&&(currentWord[i]==originalWord[i+1]||
						currentWord[i]==originalWord[originalWord.length-1])){
					currentContentsAsCells[i]=new Cell(currentWord[i], Cell.YELLOW);
				}else if(i==currentWord.length-1&&(currentWord[i]==originalWord[i-1]||
						currentWord[i]==originalWord[0])){
					currentContentsAsCells[i]=new Cell(currentWord[i], Cell.YELLOW);
				}
			}
		}
		return currentContentsAsCells;
	}

	/*Returns the number of random transformations applied to the word while 
	 *the puzzle was being generated.
	 */
	public int getNumOfInitTransformations(){
		return numberOfTransformationsDone;
	}

	/*
	 * Returns the length(number of characters) of the puzzle solution
	 */
	public int getPuzzleLength(){
		return originalWord.length;
	}

	/*
	 * Returns a String representing the word the user is expected to guess
	 */
	public String getSolution(){
		String returnString=new String();
		for(int i=0;i<originalWord.length;i++){
			returnString+=originalWord[i];
		}
		return returnString;
	}

	/*
	 * Given two positions firstCellSelected and secondCellSelected , 
	 * this transformation moves the character at position firstCellSelected
	 * to position secondCellSelected. All the characters in between are then
	 * shifted by one position, either to the right or left, to make room for
	 * the moved character. 
	 */
	public void insert(int firstCellSelected, int secondCellSelected){
		char[] tempArray=new char[currentWord.length];
		
		for(int x=0;x<tempArray.length;x++){
			tempArray[x]=currentWord[x];
		}
		
		tempArray[secondCellSelected]=currentWord[firstCellSelected];
		if(firstCellSelected<secondCellSelected){
			for(int i=firstCellSelected;i<secondCellSelected;i++){
				tempArray[i]=currentWord[i+1];
			}
		}else if(secondCellSelected<firstCellSelected){
			for(int i=firstCellSelected;i>secondCellSelected;i--){
				tempArray[i]=currentWord[i-1];
			}
		}

		//Copies currentWord to tempArray
		for(int p=0;p<tempArray.length;p++){
			currentWord[p]=tempArray[p];
		}
		numberOfAttempts++;
	}

	/*
	 * Determines if the current puzzle is in a correct solution state
	 */
	public boolean isSolutionCorrect(){
		boolean currentCorrect=true;
		for(int i=0;i<currentWord.length;i++){
			if(currentWord[i]!=originalWord[i]){
				currentCorrect=false;
				break;
			}
		}
		return currentCorrect;
	}

	/*
	 * Given two positions firstCellSelected and secondCellSelected, this 
	 * transformation swaps pairs of characters between firstCellSelected and 
	 * secondCellSelected, from the outermost pair to the innermost pair. 
	 */
	public void multipleSwap(int firstCellSelected, int secondCellSelected){
		char[] tempArray=new char[currentWord.length];
		for(int x=0;x<tempArray.length;x++){
			tempArray[x]=currentWord[x];
		}

		if(secondCellSelected>firstCellSelected){
			for(int i=0;i<secondCellSelected-firstCellSelected+1;i++){
				tempArray[firstCellSelected+i]=currentWord[secondCellSelected-i];
			}
		}else if(firstCellSelected>secondCellSelected){
			for(int i=0;i<firstCellSelected-secondCellSelected+1;i++){
				tempArray[firstCellSelected-i]=currentWord[secondCellSelected+i];
			}
		}

		//Copies tempArray to currentWord
		for(int i=0;i<tempArray.length;i++){
			currentWord[i]=tempArray[i];
		}
		numberOfAttempts++;
	}

	/*
	 * Given two positions firstCellSelected and secondCellSelected this
	 * transformation swaps the characters at those positions.
	 */
	public void swap(int firstCellSelected, int secondCellSelected){
		int smallIndex=firstCellSelected, bigIndex=secondCellSelected;
		char[] tempArray=new char[currentWord.length];
		
		for(int x=0;x<tempArray.length;x++){
			tempArray[x]=currentWord[x];
		}
		
		if(firstCellSelected>secondCellSelected){
			smallIndex=secondCellSelected;
			bigIndex=firstCellSelected;
		}

		tempArray[smallIndex]=currentWord[bigIndex];
		tempArray[bigIndex]=currentWord[smallIndex];

		//Copies tempArray to currentWord
		for(int i=0;i<tempArray.length;i++){
			currentWord[i]=tempArray[i];
		}

		numberOfAttempts++;
	}

	/*
	 * Returns a String representation of the current state of the puzzle.
	 */
	public String toString(){
		String returnString=new String();
		for(int i=0;i<currentWord.length;i++){
			returnString+=currentWord[i];
		}
		return returnString;
	}

}