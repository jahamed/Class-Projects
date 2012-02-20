import java.awt.Color;
import CMSC131GridTools.DrawingGrid;

public class LetterMaker {

	public static void drawLetter(DrawingGrid grid, char letter, Color color) {

		int size = grid.getScale();
		final int BRUSHWIDTH=3;

		//For Letter L

		if (letter == 'L'){
			int col=0, row=0;
			//Prints Col
			while (col<BRUSHWIDTH){
				while (row < size){
					grid.setColor(row, col, color);
					row++;
				}
				row=0;
				col++;
			}
			//Prints Row
			row=size-3;
			while (row<size){
				while (col<size){
					grid.setColor(row, col, color);
					col++;
				}
				col=0;
				row++;			
			}
		}

		//For Letter O

		if (letter == 'O'){
			int col=0, row=0;
			//Prints ColLeft
			while (col<BRUSHWIDTH){
				while (row < size){
					grid.setColor(row, col, color);
					row++;
				}
				row=0;
				col++;
			}
			//Prints RowTop
			while (row<BRUSHWIDTH){
				while (col<size){
					grid.setColor(row, col, color);
					col++;
				}
				col=0;
				row++;
			}

			//Prints RowBottom
			row=size-3;
			while (row<size){
				while (col<size){
					grid.setColor(row, col, color);
					col++;
				}
				col=0;
				row++;			
			}

			//Prints ColRight
			row=0;
			col=size-3;
			while (col<size){
				while (row<size){
					grid.setColor(row, col, color);
					row++;
				}
				row=0;
				col++;
			}
		}

		//For Letter J
		if (letter == 'J'){
			int col=0, row=0;

			//Prints JLeftHook
			row=(size/2)+1;
			while (col<BRUSHWIDTH){
				while (row<size){
					grid.setColor(row, col, color);
					row++;
				}
				col++;
				row=(size/2)+1;
			}
			//Prints RowBottom
			row=size-3;
			col=0;
			while (row<size){
				while (col<size){
					grid.setColor(row, col, color);
					col++;
				}
				col=0;
				row++;			
			}

			//Prints ColRight
			row=0;
			col=size-3;
			while (col<size){
				while (row<size){
					grid.setColor(row, col, color);
					row++;
				}
				row=0;
				col++;
			}
		}

		//For Letter H
		if (letter == 'H'){
			int col=0, row=0;
			//Prints ColLeft
			while (col<BRUSHWIDTH){
				while (row < size){
					grid.setColor(row, col, color);
					row++;
				}
				row=0;
				col++;
			}

			//Prints ColRight
			row=0;
			col=size-3;
			while (col<size){
				while (row<size){
					grid.setColor(row, col, color);
					row++;
				}
				row=0;
				col++;
			}

			//Prints Middle
			row=(size/2)-1;
			col=0;
			while (row<size){
				while (col<size && row<=(size/2)+1){
					grid.setColor(row, col, color);
					col++;
				}
				col=0;
				row++;
			}
		}

		//For Letter X
		if (letter == 'X'){
			int col=0, row = 0;

			//TB Center Line
			while (col<size){
				grid.setColor(row, col, color);
				col++;
				row++;
			}
			col=0;
			row=0;

			while (col<size-1){
				grid.setColor(row+1, col, color);
				col++;
				row++;
			}
			col=0;
			row=0;

			while (col<size-1){
				grid.setColor(row, col+1, color);
				col++;
				row++;
			}	
			row=size-1;
			col=0;
			while (col<size){
				grid.setColor(row, col, color);
				col++;
				row--;
			}
			row=size-1;
			col=0;
			while (col<size-1){
				grid.setColor(row-1, col, color);
				col++;
				row--;
			}
			row=size-1;
			col=0;
			while (col<size-1){
				grid.setColor(row, col+1, color);
				col++;
				row--;
			}
		}

		//For Letter Y
		if (letter == 'Y'){
			int col=0, row=0;

			//TB Center Line
			while (col<size/2){
				grid.setColor(row, col, color);
				col++;
				row++;
			}
			col=0;
			row=0;

			while (col<(size/2)-1){
				grid.setColor(row+1, col, color);
				col++;
				row++;
			}
			col=0;
			row=0;

			while (col<(size/2)-1){
				grid.setColor(row, col+1, color);
				col++;
				row++;
			}	
			row=0;
			col=size-1;

			while (col>(size/2)){
				grid.setColor(row, col, color);
				col--;
				row++;
			}
			row=0;
			col=size-1;
			while (col>(size/2)-1){
				grid.setColor(row, col-1, color);
				col--;
				row++;
			}
			row=0;
			col=size-1;
			while (col>(size/2)-1){
				grid.setColor(row+1, col, color);
				col--;
				row++;
			}
			row=(size/2)-1;
			col=(size/2)-1;
			while (row<size){
				while (col<=(size/2)+1){
					grid.setColor(row, col, color);
					col++;
				}
				col=(size/2)-1;
				row++;
			}

		}
	}
}