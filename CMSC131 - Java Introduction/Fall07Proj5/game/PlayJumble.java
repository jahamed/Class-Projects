package game;
import puzzleLib.PuzzleGUI;



/**
 * Driver for the Puzzle game.  This class contains a main method that 
 * will run the game using the GUI provided.
 *
 */

public class PlayJumble {
	public static void main(String[] args) {
		new PlayJumble();
	}
	
	/**
	 *  Start the game, using the GUI.
	 *
	 */
	public PlayJumble() {
		
		/* 
		 * The following method forces the random generator
		 * to generate the same sequence of values.
		 * Useful for development.
		 */
		 /* Random131.setDeterministic(); */ 
		
		
		/* Creating the puzzle engine */
        Jumble puzzle = new Jumble();
        
        /* Creating the interface object, and associating it with the engine */
		PuzzleGUI puzzleGUI = new PuzzleGUI("My Puzzle", puzzle);
		
		/* Starting the game */
		puzzleGUI.startGame();
	}
}