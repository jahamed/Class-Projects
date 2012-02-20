
import junit.framework.TestCase;
import game.Jumble;
import puzzleLib.*;
 
public class StudentTests extends TestCase {

	public void testGeneratePuzzle(){
		Jumble testJumble=new Jumble();
		String wordToPassIn="Foobar";
		testJumble.generatePuzzle(wordToPassIn);
		System.out.println(testJumble.getSolution());
		for(int i=0;i<testJumble.getSolution().length();i++){
			assertEquals(testJumble.getSolution().charAt(i), wordToPassIn.charAt(i));
		}
		for(int h=0;h<testJumble.getPuzzleLength();h++){
			assertEquals(testJumble.toString().charAt(h), wordToPassIn.charAt(h));
		}
	}
	
	public void testSwap(){
		Jumble testJumble=new Jumble();
		String wordToUse="melody";
		testJumble.generatePuzzle(wordToUse);
		testJumble.swap(1,4);
		assertEquals(testJumble.toString(), "mdloey");
		testJumble.swap(5,0);
		assertEquals(testJumble.toString(), "ydloem");
		wordToUse="a";
		testJumble.generatePuzzle(wordToUse);
		testJumble.swap(0,0);
		assertEquals(testJumble.toString(), "a");
		//System.out.println(testJumble.toString());	
	}
	
	public void testInsert(){
		Jumble testJumble=new Jumble();
		String wordToUse="musical";
		testJumble.generatePuzzle(wordToUse);
		testJumble.insert(1,4);
		assertEquals(testJumble.toString(), "msicual");
		testJumble.insert(5,1);
		assertEquals(testJumble.toString(), "masicul");
		testJumble.insert(2,2);
		assertEquals(testJumble.toString(), "masicul");
		wordToUse="p";
		testJumble.generatePuzzle(wordToUse);
		testJumble.insert(0,0);
		assertEquals(testJumble.toString(), "p");
		wordToUse="anthropomorphically";
		testJumble.generatePuzzle(wordToUse);
		testJumble.insert(7,1);
		assertEquals(testJumble.toString(), "aonthropmorphically");
		testJumble.insert(0,3);
		assertEquals(testJumble.toString(), "ontahropmorphically");
		
	}
	
	public void testMultipleSwap(){
		Jumble testJumble=new Jumble();
		String wordToUse="melody";
		testJumble.generatePuzzle(wordToUse);
		testJumble.multipleSwap(1,4);
		assertEquals(testJumble.toString(), "mdoley");
		testJumble.multipleSwap(5,1);
		assertEquals(testJumble.toString(), "myelod");
		wordToUse="aonthropmorphically";
		testJumble.generatePuzzle(wordToUse);
		testJumble.multipleSwap(10,5);
		assertEquals(testJumble.toString(),"aonthromporphically");
		testJumble.multipleSwap(0,0);
		assertEquals(testJumble.toString(),"aonthromporphically");
		wordToUse="n";
		testJumble.generatePuzzle(wordToUse);
		testJumble.multipleSwap(0,0);
		assertEquals(testJumble.toString(),"n");
	}
	
	public void testGetCurrentContentsAsCells(){
		Jumble testJumble=new Jumble();
		String wordToUse="computer";
		testJumble.generatePuzzle(wordToUse);
		testJumble.swap(6,7);
		//currentWord="computre"
		Cell[] tempCell={new Cell('c',Cell.WHITE),new Cell('o',Cell.WHITE),
				new Cell('m',Cell.WHITE),new Cell('p',Cell.WHITE),
				new Cell('u',Cell.WHITE),new Cell('t',Cell.WHITE),
				new Cell('r',Cell.YELLOW),new Cell('e',Cell.YELLOW)};
		for(int i=0;i<wordToUse.length();i++){
			assertEquals(testJumble.getCurrentContentsAsCells()[i].getColor(),tempCell[i].getColor());
			assertEquals(testJumble.getCurrentContentsAsCells()[i].getCharacter(),tempCell[i].getCharacter());
		}
		wordToUse="foobar";
		testJumble.generatePuzzle(wordToUse);
		testJumble.swap(0,1);
		//currentWord="ofobar"
		testJumble.swap(2,5);
		//currentWord="ofrbao"
		Cell[] tempCell2={new Cell('o',Cell.YELLOW),new Cell('f',Cell.YELLOW),
				new Cell('r',Cell.WHITE),new Cell('b',Cell.WHITE),
				new Cell('a',Cell.WHITE),new Cell('o',Cell.WHITE)};
		for(int i=0;i<wordToUse.length();i++){
			assertEquals(testJumble.getCurrentContentsAsCells()[i].getColor(),tempCell2[i].getColor());
			assertEquals(testJumble.getCurrentContentsAsCells()[i].getCharacter(),tempCell2[i].getCharacter());
		}
		testJumble.swap(0,2);
		//currentWord="rfobao"
		testJumble.swap(5,3);
		//currentWord="rfooab"
		Cell[] tempCell3={new Cell('r',Cell.YELLOW),new Cell('f',Cell.YELLOW),
				new Cell('o',Cell.WHITE),new Cell('o',Cell.YELLOW),
				new Cell('a',Cell.WHITE),new Cell('b',Cell.WHITE)};
		for(int i=0;i<wordToUse.length();i++){
			assertEquals(testJumble.getCurrentContentsAsCells()[i].getColor(),tempCell3[i].getColor());
			assertEquals(testJumble.getCurrentContentsAsCells()[i].getCharacter(),tempCell3[i].getCharacter());
		}	
	}
	
	public void testToString(){
		Jumble testJumble=new Jumble();
		String wordToUse="Foobar";
		testJumble.generatePuzzle(wordToUse);
		assertTrue(testJumble.toString().equals(wordToUse));
	}
}
