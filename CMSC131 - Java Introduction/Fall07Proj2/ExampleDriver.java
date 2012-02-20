import java.awt.Color;
import java.util.Scanner;
import CMSC131GridTools.DrawingGrid;

/**
 *  THIS CLASS IS PROVDED FOR YOU.  USE IT TO TEST THE LETTERMAKER
 *  CLASS THAT YOU ARE WRITING.
 *   
 *  This driver relies on the "drawLetter" method of the "LetterMaker"
 *  class.  It prompts the user to enter information about what letter
 *  he/she would like to see.  Then it creates a DrawingGrid, and calls
 *  the drawLetter method of the LetterMaker class to actually draw
 *  the letter.
 */
public class ExampleDriver {
	
	public static void main(String[] args) {
		
		Scanner scanner = new Scanner(System.in);
		
		/* Get input from user about what letter to draw */
		System.out.print("Choose a letter (L, O, J, H, X, or Y):  ");
		String choice = scanner.next();
		System.out.print("Choose a size (odd value, 9 or larger): ");
		int size = scanner.nextInt();		
		System.out.print("Choose color (red, green, blue): ");
		String colorInput = scanner.next();
		
		/* Create Color that will be used to draw the letter */
		Color color;
		if (colorInput.equals("red"))
			color = Color.RED;
		else if (colorInput.equals("green"))
			color = Color.GREEN;
		else if (colorInput.equals("blue"))
			color = Color.BLUE;
		else 
			color = Color.BLACK;
		
		/* Create drawing grid of the size requested */
		DrawingGrid grid = new DrawingGrid(size);
		
		/* Draw the letter on the grid */
		LetterMaker.drawLetter(grid, choice.charAt(0), color);
		
	}
}
