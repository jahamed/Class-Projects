package CMSC131GridTools;
import java.awt.Dimension;
import java.awt.Graphics;
import javax.swing.JPanel;
import javax.swing.JFrame;
import javax.swing.WindowConstants;
import java.awt.Color;

/**
 * WARNING:  READING THIS CODE MAY CONFUSE YOU PRETTY BADLY!!!
 * 
 * I've decided to include this source code in the project in case you
 * are curious to see an example of more advanced Java programming.
 * 
 * You should not modify this file in any way.
 * 
 * You should not even READ this file unless you are very curious and
 * not easily scared!
 * 
 */
public class DrawingGrid extends JPanel {
	
	protected static final long serialVersionUID = 0L;
	protected static final int MARGIN_SIZE = 5;
	protected int scale;
	protected Color[][] colors;
	private static final int SQUARE_SIZE = 15;  // pixel size of each square
	private JFrame frame;
	
	protected DrawingGrid() {
	}
	
	public DrawingGrid(int scale) {
		this.scale = scale;
		int overallSize = scale + 2 * MARGIN_SIZE;
		colors = new Color[overallSize][overallSize];
		for (int i = 0; i < overallSize; i++)
			for (int j = 0; j < overallSize; j++)
				colors[i][j] = Color.WHITE;
		
		javax.swing.SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				Thread.currentThread().setPriority(Thread.MAX_PRIORITY);
				createAndShowFrame();
			}
		});	
	}
	
	public int getScale() {
		return scale;
	}
	
	private void createAndShowFrame() {
		frame = new JFrame("Drawing Grid");
		frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		setSize((scale + 2 * MARGIN_SIZE) * SQUARE_SIZE, (scale + 2 * MARGIN_SIZE) * SQUARE_SIZE);
		frame.setContentPane(this);
		frame.pack();
		frame.setVisible(true);
		frame.toFront();
		frame.setAlwaysOnTop(true);
	}
	
	public void setColor(int row, int col, Color color) {
		colors[row + MARGIN_SIZE][col + MARGIN_SIZE] = color;
		this.repaint();
	}
	
	public void kill() {
		if (frame != null)
			frame.dispose();
	}
	
	public Dimension getPreferredSize() {
		return new Dimension((scale + 2 * MARGIN_SIZE) * SQUARE_SIZE + 1, (scale + 2 * MARGIN_SIZE) * SQUARE_SIZE + 1);
	}
	
	public void paint(Graphics g) {
		super.paint(g);
	
		int offset = MARGIN_SIZE * SQUARE_SIZE;
		
		for (int i = 0; i < scale + 2 * MARGIN_SIZE; i ++)
			for (int j = 0; j < scale + 2 * MARGIN_SIZE; j++) {
				g.setColor(colors[i][j]);
				g.fillRect(j * SQUARE_SIZE + 1, i * SQUARE_SIZE + 1, SQUARE_SIZE, SQUARE_SIZE);
			}
		g.setColor(Color.BLACK);
		for (int i = 0; i < scale + 1; i++) 
			g.drawLine(offset + i * SQUARE_SIZE, offset, offset + i * SQUARE_SIZE, offset + scale * SQUARE_SIZE);
		for (int j = 0; j < scale + 1; j++) 
			g.drawLine(offset, offset + j * SQUARE_SIZE, offset + scale * SQUARE_SIZE, offset + j * SQUARE_SIZE);
	}
}
