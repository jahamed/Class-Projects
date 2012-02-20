package fishPond;

import java.util.*;
import javax.swing.*;
import java.awt.*;
import javax.swing.event.*;
import cmsc131Utilities.ImageLoader;
import java.awt.event.*;

/** THIS CLASS HAS BEEN WRITTEN FOR YOU -- DO NOT MODIFY IT!
 * <p>
 * This is the View of the M-V-C design pattern.
 * <p>
 * @author Fawzi Emad Copyright (C) 2005
 */
public class View extends JPanel {
	
	/* Static Field required for any serializable class */
	private static final long serialVersionUID = 0;
	
	/* Size (in pixels) of individual images (fish, plant, rock, water) */
	private static final int ICON_WIDTH = 20;
	private static final int ICON_HEIGHT = 20;
	
	/* Images */
	private static Image waterShape;
	private static Image rockShape;
	private static Image[][] fishShapes = new Image[4][9];  // [direction][size]
	private static Image[] plantShapes = new Image[9];      // [size]
	
	/* Copy of the Model of the M-V-C setup.  The View maintains it's own copy of 
	 * the Model so that when the GUI-Drawing-Thread gets around to rendering the 
	 * artwork, it has an immutable copy to draw.*/
	private Model copyOfModel;
	
	/* Cutoffs regarding size that determine when to switch to the next size icon */
	private int[] fishSizeCutoffs = new int[8];
	private int[] plantSizeCutoffs = new int[8];
	
	/* The GUI Frame. (Actual window that will contain this View and the other 
	 * widgets.) */
	private JFrame frame;
	
	/* Widgets for the GUI */
	private JLabel fishCountLabel = new JLabel("Fish: 0");
	private JLabel plantCountLabel = new JLabel("Plants: 0");
	private JLabel speedLabel = new JLabel("SPEED");
	private JSlider slider = new JSlider(0, 100);
	private JTextField rowsField, colsField, rockCountField, fishCountField, plantCountField;
	private JButton restartButton = new JButton("Restart");
	private JButton differentPondButton = new JButton("New Pond");
	
	/* Where to put the slider the first time (range is 0-100) */
	private static final int INITIAL_SLIDER_POSITION = 50;
	
	public View(Model model, int rows, int cols, int rockCount, int fishCount, 
			int plantCount) {
		
		copyOfModel = model;
		
		/* Figure out what size icons to use based on actual size of object */
		calculateFishSizeCutoffs();
		calculatePlantSizeCutoffs();
		
		/* Load images from files */
		waterShape = ImageLoader.getImage("Images/water.JPG");
		rockShape = ImageLoader.getImage("Images/rock.JPG");
		String[] directionNames = {"Up", "Down", "Left", "Right"};
		for (int dir = 0; dir < 4; dir++) {
			for (int size = 0; size < 9; size++) {
				String name = "Images/fish"+ directionNames[dir] + (size + 1) + ".JPG";
				fishShapes[dir][size] = ImageLoader.getImage(name);
			}
		}
		for (int size = 0; size < 9; size++) {
			String name = "Images/plant" + (size + 1) + ".JPG";
			plantShapes[size] = ImageLoader.getImage(name);
		}
		
		/* Initialize widgets */
		slider.setValue(INITIAL_SLIDER_POSITION);
		rowsField = new JTextField("" + rows, 3);
		colsField = new JTextField("" + cols, 3);
		rockCountField = new JTextField("" + rockCount, 3);
		fishCountField = new JTextField("" + fishCount, 3);
		plantCountField = new JTextField("" + plantCount, 3);
		
		/* Create top-level window */
		frame = new JFrame("FISH CLUB!");
		
		/* Create container to put everything into */
		JPanel overall = new JPanel();
		frame.setContentPane(overall);
		
		/* Create top and bottom containers */
		JPanel bottomPanel = new JPanel();
		JPanel topPanel = new JPanel();
		
		/* Put widgets into bottom panel */
		bottomPanel.add(fishCountLabel);
		bottomPanel.add(Box.createHorizontalStrut(15));
		bottomPanel.add(plantCountLabel);
		bottomPanel.add(Box.createHorizontalStrut(30));
		bottomPanel.add(speedLabel);
		bottomPanel.add(slider);
		bottomPanel.add(Box.createHorizontalStrut(30));
		bottomPanel.add(restartButton);
		
		/* Put widgets into top panel */
		topPanel.add(new JLabel("Rows: "));
		topPanel.add(rowsField);
		topPanel.add(Box.createHorizontalStrut(15));
		topPanel.add(new JLabel("Cols: "));
		topPanel.add(colsField);
		topPanel.add(Box.createHorizontalStrut(15));
		topPanel.add(new JLabel("Fish: "));
		topPanel.add(fishCountField);
		topPanel.add(Box.createHorizontalStrut(15));
		topPanel.add(new JLabel("Rocks: "));
		topPanel.add(rockCountField);
		topPanel.add(Box.createHorizontalStrut(15));
		topPanel.add(new JLabel("Plants: "));
		topPanel.add(plantCountField);
		topPanel.add(Box.createHorizontalStrut(30));
		topPanel.add(differentPondButton);
		
		/* Choose "borderlayout" as the layout manager */
		overall.setLayout(new BorderLayout());
		
		/* Put the three layers into the overall container */
		overall.add(topPanel, BorderLayout.NORTH);
		overall.add(bottomPanel, BorderLayout.SOUTH);
		overall.add(this,BorderLayout.CENTER);  // "this" is the pond itself
		
		/* Set so that if someone closes the window, the whole program shuts down */
		frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		
		/* Re-size frame so that everything fits snugly */
		frame.pack();
		
		/* Make frame visible */
		frame.setVisible(true);	
	}

	/**
	 * Register a "ChangeListener" with the Slider in the GUI. 
	 */
	public void registerSliderListener(ChangeListener changeListener) {
		slider.addChangeListener(changeListener);
	}
	
	/** 
	 * Register an "ActionListener" with the Restart Button in the GUI.
	 */
	public void registerRestartButtonListener(ActionListener actionListener) {
		restartButton.addActionListener(actionListener);
	}
	
	/**
	 * Register an "ActionListener" with the "New Pond" button in the GUI. 
	 */
	public void registerDifferentPondButtonListener(ActionListener actionListener) {
		differentPondButton.addActionListener(actionListener);
	}
	
	/**
	 * Return the position of the slider (0 - 100)
	 */
	public int getSliderPosition() {
		return slider.getValue();
	}

	/**
	 * Return value of rows field entered by the user into the GUI
	 */
	public int getRows() {
		return Integer.valueOf(rowsField.getText());
	}
	
	/**
	 * Return value of the cols field entered by the user into the GUI
	 */
	public int getCols() {
		return Integer.valueOf(colsField.getText());
	}
	
	/** 
	 * Return the value of the "rocks" field entered by the user into the GUI
	 */
	public int getRockCount() {
		return Integer.valueOf(rockCountField.getText());
	}
	
	/**
	 * Return the value of the "fish" field entered by the user into the GUI
	 */
	public int getFishCount() {
		return Integer.valueOf(fishCountField.getText());
	}
	
	/**
	 * Return the value of the "plants" field entered by the user into the GUI
	 */
	public int getPlantCount() {
		return Integer.valueOf(plantCountField.getText());
	}
	
	/* Figure out cutoffs for what size fish icon (0-8) to draw based on the sizes 
	 * of fish */
	private void calculateFishSizeCutoffs() {
		for (int i = 1; i < 9; i++)
			fishSizeCutoffs[i - 1] = (int)((i * i * i) / (double) 1000 * Fish.MAX_FISH_SIZE);
	}
	
	/* Figure out cutoffs for what size plant icon (0-8) to draw based on sizes of the 
	 * plants */
	private void calculatePlantSizeCutoffs() {
		for (int i = 1; i < 9; i++)
			plantSizeCutoffs[i - 1] = (int)((i * i * i) / (double) 1000 * Plant.MAX_PLANT_SIZE);
	}
	
	/* Calculate which fish icon to draw for a given size */
	private int calculateFishIconSize(int s) {
		for (int i = 0; i < 8; i++) {
			if (s < fishSizeCutoffs[i])
				return i;
		}
		return 8;
	}
	
	/* Calculate which plant icon to draw for a given size */
	private int calculatePlantIconSize(int s) {
		for (int i = 0; i < 8; i++) {
			if (s < plantSizeCutoffs[i])
				return i;
		}
		return 8;
	}
	
	/** Tells Java GUI-drawing-thread how big this component should be drawn */
	public Dimension getPreferredSize() {
		return new Dimension(copyOfModel.getCols() * ICON_WIDTH, copyOfModel.getRows() * ICON_HEIGHT);
	}
	
	/** The controller calls this method to let the View know that the model
	 * has changed.  The parameter will be a COPY of the model to be drawn by
	 * the GUI-drawing-thread whenever it feels like it.  */
	public void updateYourself(Model copyOfModel) {
	
		this.copyOfModel = copyOfModel;

		/* Set the data counters */
		fishCountLabel.setText("Fish: " + copyOfModel.getFish().size());
		plantCountLabel.setText("Plants: " + copyOfModel.getPlants().size());
		
		this.repaint();  // suggest that GUI should be redrawn
	}
	
	/** Called by the GUI-drawing-thread when it is time to re-draw the View */
	public void paint(Graphics g) {
		
		/* Keep local reference to our copy of the model in case copyOfModel is 
		 * updated while this thread (GUI-Drawing) is in the middle of drawing
		 * the pretty pictures. */
		Model localReferenceToCopyOfModel = copyOfModel;
		
		/* Make sure all of the built-in drawing behavior is done for us (this
		 * will ensure that the widgets other than the actual pond are drawn) */
		super.paint(g);
		
		/* Draw the water and rock shapes */
		for (int i = 0; i < localReferenceToCopyOfModel.getRows(); i++)
			for (int j = 0; j < localReferenceToCopyOfModel.getCols(); j++) {
				boolean shape = localReferenceToCopyOfModel.getShape(i, j);
				Image shapeToDraw;
				if (shape == Model.WATER)
					shapeToDraw = waterShape;
				else
					shapeToDraw = rockShape;
				g.drawImage(shapeToDraw, j * ICON_WIDTH, i * ICON_HEIGHT, null);	
			}
		
		/* Draw the plants */
		Iterator<Plant> m = localReferenceToCopyOfModel.getPlants().iterator();
		while(m.hasNext()) {
			Plant curr = m.next();
			if (curr.isAlive()) {
				int sizeToDraw = calculatePlantIconSize(curr.getSize());
				g.drawImage(plantShapes[sizeToDraw], curr.getCol() * ICON_HEIGHT, curr.getRow() * ICON_WIDTH, null);
			}
		}
		
		/* Draw the fish */
		Iterator<Fish> k = localReferenceToCopyOfModel.getFish().iterator();
		while(k.hasNext()) {
			Fish curr = k.next();
			if (curr.isAlive()) {
				int sizeToDraw = calculateFishIconSize(curr.getSize());
				int dir = curr.getDirection();
				int directionShape;
				if (dir == Fish.UP)
					directionShape = 0;
				else if (dir == Fish.DOWN)
					directionShape = 1;
				else if (dir == Fish.LEFT)
					directionShape = 2;
				else if (dir == Fish.RIGHT)
					directionShape = 3;
				else
					throw new IllegalFishDirectionException(dir);
				g.drawImage(fishShapes[directionShape][sizeToDraw], curr.getCol() * ICON_HEIGHT, curr.getRow() * ICON_WIDTH, null);
			}
		}	
	}
	
	/** Re-size the GUI so that everything fits snugly. */
	public void rePack() {
		frame.pack();
	}
}
